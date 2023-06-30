using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;

namespace CW
{
    class Program
    {
        private static void Main(string[] args)
        {
            string pathToData = "";
            string inputPath = "test.txt";
            string outputPath = "answer.txt";

            List<RoaringBitmap> phase1 = new List<RoaringBitmap>();
            List<RoaringBitmap> phase2 = new List<RoaringBitmap>();
            List<string> keyColumnNames;

            keyColumnNames = ReadRequest(inputPath, phase1, phase2, pathToData);
            CreateBitmapsWithFactKeys(keyColumnNames, phase1, phase2, pathToData);

            for (int i = 1; i < phase2.Count; i++)
                phase2[0].And(phase2[i]);

            PrintResult(inputPath, phase2.Count > 0 ? phase2[0] : null, outputPath, pathToData);
        }

        /// <summary>
        /// Материализация результата фильтрации (3 фаза).
        /// </summary>
        /// <param name="inputPath">путь к файлу с запросом</param>
        /// <param name="roaringBitmap">битмап с результатом фильтрации</param>
        /// <param name="outputPath">путь к файлу для вывода результата</param>
        private static void PrintResult(string inputPath, RoaringBitmap roaringBitmap, string outputPath, string pathToData)
        {
            try
            {
                string requestColumns;
                using (StreamReader sr = new StreamReader(inputPath))
                {
                    requestColumns = sr.ReadLine();
                }

                string[] columnNames = requestColumns.Split(',');
                List<StringBuilder> lines = new List<StringBuilder>();

                using (StreamWriter sw = new StreamWriter(outputPath, true))
                {
                    for (int i = 0; i < columnNames.Length; i++)
                    {
                        if (columnNames[i].Contains("FactResellerSales"))
                        {
                            using (StreamReader sr = new StreamReader(Path.Combine(pathToData, columnNames[i]) + ".csv"))
                            {
                                int j = 0;
                                string stringLine;
                                int l = 0;

                                while ((stringLine = sr.ReadLine()) != null && stringLine.Length > 0)
                                {
                                    if (roaringBitmap != null && roaringBitmap.Get((uint)j))
                                    {
                                        if (i == columnNames.Length - 1 && i != 0)
                                            sw.WriteLine(lines[l++].Append("|").Append(stringLine));
                                        else if (i == columnNames.Length - 1 && l == 0)
                                            sw.WriteLine(stringLine);
                                        else if (i > 0)
                                            lines[l++].Append("|").Append(stringLine);
                                        else
                                            lines.Add(new StringBuilder(stringLine));
                                    }
                                    else if (roaringBitmap == null)
                                    {
                                        if (i == columnNames.Length - 1 && i != 0)
                                            sw.WriteLine(lines[l++].Append("|").Append(stringLine));
                                        else if (i == columnNames.Length - 1 && l == 0)
                                            sw.WriteLine(stringLine);
                                        else if (i > 0)
                                            lines[l++].Append("|").Append(stringLine);
                                        else
                                            lines.Add(new StringBuilder(stringLine));
                                    }
                                    j++;
                                }
                            }
                        }
                        else
                        {
                            using (StreamReader sr = new StreamReader(Path.Combine(pathToData, columnNames[i].Split('.')[0]) + ".csv"))
                            {
                                string keyColumnName = (columnNames[i].Split('.')[0]).Replace("Dim", "") + "Key";

                                if (keyColumnName.Equals("DateKey"))
                                    keyColumnName = "OrderDateKey";

                                List<int> extKeys = GetExtKeys(Path.Combine(pathToData, "FactResellerSales." + keyColumnName + ".csv"), roaringBitmap);
                                var props = Type.GetType("CW." + columnNames[i].Split('.')[0]).GetProperties();
                                int columnIndex = GetColumnIndex(columnNames[i].Split('.')[1], props);

                                int l = 0;
                                string stringLine;
                                Dictionary<int, string> dimKeyValue = new Dictionary<int, string>();

                                while ((stringLine = sr.ReadLine()) != null && stringLine.Length > 0)
                                {
                                    string[] columns = stringLine.Split('|');
                                    dimKeyValue[int.Parse(columns[0])] = columns[columnIndex];
                                }

                                for (int j = 0; j < extKeys.Count; j++)
                                {
                                    if (i == columnNames.Length - 1 && i != 0)
                                        sw.WriteLine(lines[l++].Append("|").Append(dimKeyValue[extKeys[j]]));
                                    else if (i == columnNames.Length - 1 && l == 0)
                                        sw.WriteLine(dimKeyValue[extKeys[j]]);
                                    else if (i > 0)
                                        lines[l++].Append("|").Append(dimKeyValue[extKeys[j]]);
                                    else
                                        lines.Add(new StringBuilder(dimKeyValue[extKeys[j]]));
                                }
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        /// <summary>
        /// Достает внешние ключи по названию файла с нужным столбцом.
        /// </summary>
        /// <param name="fileName">путь к файлу со столбцом с ключами</param>
        /// <param name="roaringBitmap">битмап с результатом фильтрации</param>
        /// <returns>внешние ключи</returns>
        private static List<int> GetExtKeys(string fileName, RoaringBitmap roaringBitmap)
        {
            List<int> extKeys = new List<int>();

            using (StreamReader keysSr = new StreamReader(fileName))
            {
                string sLine;

                int j = 0;
                while ((sLine = keysSr.ReadLine()) != null && sLine.Length > 0)
                {
                    int key = int.Parse(sLine);

                    if (roaringBitmap != null && roaringBitmap.Get((uint)j))
                        extKeys.Add(key);
                    else if (roaringBitmap == null)
                        extKeys.Add(key);
                    j++;
                }
            }

            return extKeys;
        }

        /// <summary>
        /// Строит битмапы по таблице фактов (2 фаза).
        /// </summary>
        /// <param name="keyColumnNames">названия столбцов с ключами в таблице фактов</param>
        /// <param name="phase1">первичные ключи</param>
        /// <returns>битмапы</returns>
        private static void CreateBitmapsWithFactKeys(List<string> keyColumnNames,
            List<RoaringBitmap> phase1, List<RoaringBitmap> phase2, string pathToData)
        {
            try
            {
                for (int i = 0; i < phase1.Count; i++)
                {
                    RoaringBitmap roaringBitmap = new RoaringBitmap();
                    var keyColumnName = keyColumnNames[i];

                    if (keyColumnName.Equals("DateKey"))
                        keyColumnName = "OrderDateKey";

                    using (StreamReader sr = new StreamReader(Path.Combine(pathToData, "FactResellerSales." + keyColumnName + ".csv")))
                    {
                        string stringLine;

                        int j = 0;
                        while ((stringLine = sr.ReadLine()) != null && stringLine.Length > 0)
                        {
                            int key = int.Parse(stringLine);

                            if (phase1[i].Get((uint)key))
                                roaringBitmap.Set((uint)j, true);
                            j++;
                        }
                    }

                    phase2.Add(roaringBitmap);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        /// <summary>
        /// Считывает файл с запросом.
        /// </summary>
        /// <param name="path">путь к файлу</param>
        private static List<string> ReadRequest(string path, List<RoaringBitmap> phase1, List<RoaringBitmap> phase2, string pathToData)
        {
            List<string> keyColumnNames = new List<string>();
            List<string> options = new List<string>();

            try
            {
                using (StreamReader sr = new StreamReader(path))
                {
                    sr.ReadLine();
                    int n = int.Parse(sr.ReadLine());

                    for (int i = 0; i < n; i++)
                        options.Add(sr.ReadLine());
                }

                options = options.Distinct().ToList();

                for (int i = 0; i < options.Count; i++)
                {
                    if (options[i].Contains("FactResellerSales"))
                        phase2.Add(ReadFactTableOption(options[i], pathToData));
                    else
                        phase1.Add(ReadOption(options[i], keyColumnNames, pathToData));
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }

            return keyColumnNames;
        }

        /// <summary>
        /// Строит битмап с ключами для условия из таблицы фактов.
        /// </summary>
        /// <returns>битмап с ключами</returns>
        private static RoaringBitmap ReadFactTableOption(string optionLine, string pathToData)
        {
            string[] option = optionLine.Split(' ');
            RoaringBitmap roaringBitmap = new RoaringBitmap();

            using (StreamReader sr = new StreamReader(Path.Combine(pathToData, option[0] + ".csv")))
            {
                var cl = Type.GetType("CW." + option[0].Split('.')[0]);
                var prop = cl.GetProperty(option[0].Split('.')[1]);

                int j = 0;
                string stringLine;

                if (int.TryParse(option[2], out int val))
                    while ((stringLine = sr.ReadLine()) != null && stringLine.Length > 0)
                        CompareInts(int.Parse(stringLine), val, roaringBitmap, j++.ToString(), option[1]);
                else
                    while ((stringLine = sr.ReadLine()) != null && stringLine.Length > 0)
                        CompareStrings(stringLine, option[2].Trim('\''), roaringBitmap, j++.ToString(), option[1]);
            }

            return roaringBitmap;
        }

        /// <summary>
        /// Считывает необходимые столбцы и заполняет битмап первичными ключами,
        /// которые удовлетворяют предикату (фаза 1). 
        /// </summary>
        /// <param name="optionLine">строка с предикатом</param>
        /// <param name="keyColumnNames">названия считанных столбцов с ключами</param>
        /// <returns>битмап с первичными ключами</returns>
        private static RoaringBitmap ReadOption(string optionLine, List<string> keyColumnNames, string pathToData)
        {
            string[] option = optionLine.Split(' ');
            RoaringBitmap roaringBitmap = new RoaringBitmap();

            //Для случая, когда в предикате присутствуют пробелы в строке.
            if (option.Length > 3)
                for (int i = 3; i < option.Length; i++)
                    option[2] += " " + option[i];

            string tableName = option[0].Split('.')[0];
            string columnName = option[0].Split('.')[1];
            var props = Type.GetType("CW." + tableName).GetProperties();
            keyColumnNames.Add(props[0].Name);
            int columnIndex = GetColumnIndex(columnName, props);

            using (StreamReader sr = new StreamReader(Path.Combine(pathToData, tableName + ".csv")))
            {
                string stringLine;

                if (int.TryParse(option[2], out int val))
                {
                    while ((stringLine = sr.ReadLine()) != null && stringLine.Length > 0)
                    {
                        string[] columns = stringLine.Split('|');
                        CompareInts(int.Parse(columns[columnIndex]), val, roaringBitmap, columns[0], option[1]);
                    }
                }
                else
                {
                    while ((stringLine = sr.ReadLine()) != null && stringLine.Length > 0)
                    {
                        string[] columns = stringLine.Split('|');
                        CompareStrings(columns[columnIndex], option[2].Trim('\''), roaringBitmap, columns[0], option[1]);
                    }
                }
            }

            return roaringBitmap;
        }

        /// <summary>
        /// Находит индекс нужного столбца по его названию.
        /// </summary>
        /// <param name="columnName">название нужного столбца</param>
        /// <param name="props">свойства класса, в котором есть необходимый столбец</param>
        /// <returns>индекс столбца</returns>
        private static int GetColumnIndex(string columnName, PropertyInfo[] props)
        {
            int columnIndex = 0;

            for (int j = 0; j < props.Length; j++)
            {
                if (props[j].Name.Equals(columnName))
                {
                    columnIndex = j;
                    break;
                }
            }

            return columnIndex;
        }

        private static void CompareInts(int propValue,
            int value, RoaringBitmap roaringBitmap, string key, string opr)
        {
            if (opr == "<>")
            {
                if (propValue != value)
                {
                    roaringBitmap.Set(uint.Parse(key), true);
                }
            }
            else if (opr == "<")
            {
                if (propValue < value)
                {
                    roaringBitmap.Set(uint.Parse(key), true);
                }
            }
            else if (opr == ">")
            {
                if (propValue > value)
                {
                    roaringBitmap.Set(uint.Parse(key), true);
                }
            }
            else if (opr == "<=")
            {
                if (propValue <= value)
                {
                    roaringBitmap.Set(uint.Parse(key), true);
                }
            }
            else if (opr == ">=")
            {
                if (propValue >= value)
                {
                    roaringBitmap.Set(uint.Parse(key), true);
                }
            }
            else if (opr == "=")
            {
                if (propValue == value)
                {
                    roaringBitmap.Set(uint.Parse(key), true);
                }
            }
        }

        private static void CompareStrings(string propValue,
            string value, RoaringBitmap roaringBitmap, string typeKey, string operation)
        {
            if (operation == "<>")
            {
                if (!propValue.Equals(value))
                {
                    roaringBitmap.Set(uint.Parse(typeKey), true);
                }
            }
            else if (operation == "=")
            {
                if (propValue.Equals(value))
                {
                    roaringBitmap.Set(uint.Parse(typeKey), true);
                }
            }
        }
    }
}
