using System;
using System.IO;
using System.Text;

namespace Homework1
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length !=  2)
            {
                Console.WriteLine("Two arguments are required");
                return;
            }

            string line = ReadStr(args[0]);
            int n = line.Length;

            //Поиск палиндромов нечетной длины.
            int odd = FindOddPalindromes(n, line);
            
            //Поиск палиндромов четной длины.
            int even = FindEvenPalindromes(n, line);

            WriteAnswer(even + odd + " " + even + " " + odd, args[1]);
        }

        /// <summary>
        /// Записывает результат в файл
        /// </summary>
        /// <param name="ans">результат</param>
        /// <param name="path">путь к файлу</param>
        static void WriteAnswer(string ans, string path)
        {
            try
            {
                File.WriteAllText(path, ans);
            }
            catch (IOException e)
            {
                Console.WriteLine(e.Message);
            }
        }

        /// <summary>
        /// Ищет палиндромы нечётной длины
        /// </summary>
        /// <param name="n">количество символов в строке</param>
        /// <param name="line">строка</param>
        /// <returns>количество соответствующих палиндромов</returns>
        static int FindOddPalindromes(int n, string line)
        {
            int count = 0; 
            int[] odd = new int[n];
            StringBuilder sb = new StringBuilder(line);

            int left = 0;
            int right = -1;

            for (int i = 0; i < n; i++)
            {
                int k = i > right ? 1 : Math.Min(odd[left + right - i], right - i);

                while (i + k < n && i - k >= 0 && sb[i + k] == sb[i - k])
                {
                    k++;
                }

                odd[i] = k;
                count += k;

                if (i + k - 1 > right)
                {
                    left = i - k + 1;
                    right = i + k - 1;
                }
            }

            return count;
        }

        /// <summary>
        /// Ищет палиндромы чётной длины
        /// </summary>
        /// <param name="n">количество символов в строке</param>
        /// <param name="line">строка</param>
        /// <returns>количество соответствующих палиндромов</returns>
        static int FindEvenPalindromes(int n, string line)
        {
            int count = 0;
            int[] even = new int[n];
            StringBuilder sb = new StringBuilder(line);

            int left = 0;
            int right = -1;

            for (int i = 0; i < n; ++i)
            {
                int k = i > right ? 0 : Math.Min(even[left + right - i + 1], right - i + 1);

                while (i + k < n && i - k - 1 >= 0 && sb[i + k] == sb[i - k - 1])
                {
                    k++;
                }

                even[i] = k;
                count += k;

                if (i + k - 1 > right)
                {
                    left = i - k;
                    right = i + k - 1;
                }
            }

            return count;
        }

        /// <summary>
        /// Считывает строку из файла
        /// </summary>
        /// <param name="path">путь к файлу</param>
        /// <returns>строка из файла</returns>
        static string ReadStr(string path)
        {
            string line = string.Empty;

            try
            {
                line = File.ReadAllText(path);
            }
            catch (IOException e)
            {
                Console.WriteLine(e.Message);
            }

            return line;
        }
    }
}
