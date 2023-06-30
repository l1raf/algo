using System;
using System.Collections.Generic;
using System.IO;

namespace Homework2
{
    class Program
    {
        private static Point p0;
        private static string inputPath;
        private static string outputPath;
        private static Format format;
        private static Direction order;
        private static List<Point> points;

        private static void Main(string[] args)
        {
            order = Direction.Counterclockwise;
            format = Format.Plain;
            inputPath = "test0.txt";
            outputPath = "answer0.txt";

            ReadPointsFromFile();

            if (format == Format.WellKnownTest)
            {
                PrintMultipoint();
            }

            GrahamScan();
        }

        private static void GrahamScan()
        {
            // Поиск начальной точки с минимальным значением Y
            int minY = points[0].Y;
            int index = 0;

            for (int i = 1; i < points.Count; i++)
            {
                int currY = points[i].Y;

                if (currY < minY || (minY == currY && points[i].X < points[index].X))
                {
                    minY = points[i].Y;
                    index = i;
                }
            }

            Point temp = points[index];
            points[index] = points[0];
            points[0] = temp;

            p0 = points[0];
            points.RemoveAt(0);

            // Сортируем в порядке возрастания полярного угла 
            points.Sort((a, b) =>
            {
                double atanA = Math.Atan2(a.Y - p0.Y, a.X - p0.X);
                double atanB = Math.Atan2(b.Y - p0.Y, b.X - p0.X);

                if (atanA < atanB)
                {
                    return -1;
                }
                else if (atanA > atanB)
                {
                    return 1;
                }
                else
                {
                    return (GetDistance2(p0, a) >= GetDistance2(p0, b)) ? 1 : -1;
                }
            });

            points.Insert(0, p0);

            int arrSize = 1;
            // Удаляем все точки, лежащие на одной прямой, кроме самой дальней
            for (int i = 1; i < points.Count; i++)
            {
                while (i < points.Count - 1 && GetDirection(p0, points[i], points[i + 1]) == Direction.Colinear)
                {
                    i++;
                }

                points[arrSize] = points[i];
                arrSize++;
            }

            if (arrSize < 3)
            {
                return;
            }

            MyStack convexHull = new MyStack(arrSize);

            convexHull.Push(points[0]);
            convexHull.Push(points[1]);
            convexHull.Push(points[2]);

            for (int i = 3; i < arrSize; i++)
            {
                while (GetDirection(convexHull.NextToTop(), convexHull.Top(), points[i]) != Direction.Counterclockwise)
                {
                    convexHull.Pop();
                }
                convexHull.Push(points[i]);
            }

            PrintPoints(convexHull);
        }

        /// <summary>
        /// Печатает в файл исходные данные для wkt формата 
        /// </summary>
        private static void PrintMultipoint()
        {
            string line = "MULTIPOINT (";

            for (int i = 0; i< points.Count; i++)
            {
                line += "(" + points[i].X + " " + points[i].Y + "), "; 
            }

            line = line.Remove(line.Length - 2);
            line += ")";

            try
            {
                using (StreamWriter sw = new StreamWriter(outputPath))
                {
                    sw.WriteLine(line);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }

        /// <summary>
        /// Печатает точки в файл
        /// </summary>
        /// <param name="convexHull">стек с точками выпуклой оболочки</param>
        private static void PrintPoints(MyStack convexHull)
        {
            int size = convexHull.Size();

            try
            {
                using (StreamWriter sw = new StreamWriter(outputPath, true))
                {
                    if (format == Format.Plain && order == Direction.Clockwise)
                    {
                        sw.WriteLine(size);
                        sw.WriteLine(p0.X + " " + p0.Y);
                        for (int i = 0; i < size - 1; i++)
                        {
                            Point point = convexHull.Pop();
                            sw.WriteLine(point.X + " " + point.Y);
                        }
                    }
                    else if (format == Format.Plain && order == Direction.Counterclockwise)
                    {
                        MyStack stack = new MyStack(size);
                        for (int i = 0; i < size; i++)
                        {
                            stack.Push(convexHull.Pop());
                        }

                        sw.WriteLine(size);
                        for (int i = 0; i < size; i++)
                        {
                            Point point = stack.Pop();
                            sw.WriteLine(point.X + " " + point.Y);
                        }
                    }
                    else if (order == Direction.Clockwise)
                    {
                        string line = "POLYGON ((" + p0.X + " " + p0.Y + ", ";

                        for (int i = 0; i < size; i++)
                        {
                            Point point = convexHull.Pop();
                            line += point.X + " " + point.Y + ", ";
                        }

                        line = line.Remove(line.Length - 2);
                        line += "))";
                        sw.WriteLine(line);
                    }
                    else 
                    {
                        MyStack stack = new MyStack(size);
                        for (int i = 0; i < size; i++)
                        {
                            stack.Push(convexHull.Pop());
                        }

                        string line = "POLYGON ((";
                        for (int i = 0; i < size; i++)
                        {
                            Point point = stack.Pop();
                            line += point.X + " " + point.Y + ", ";
                        }

                        line += p0.X + " " + p0.Y + "))";
                        sw.WriteLine(line);
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }

        /// <summary>
        /// Находит квадрат расстояния между точками
        /// </summary>
        /// <param name="p1">первая точка</param>
        /// <param name="p2">вторая точка</param>
        /// <returns>квдарат расстояния между точками</returns>
        private static double GetDistance2(Point p1, Point p2)
        {
            return (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y);
        }

        /// <summary>
        /// Определяет направление поворота угла
        /// </summary>
        /// <returns>направлние</returns>
        private static Direction GetDirection(Point p1, Point p2, Point p3)
        {
            int angledir = (p2.Y - p1.Y) * (p3.X - p2.X) - (p2.X - p1.X) * (p3.Y - p2.Y);

            if (angledir == 0)
            {
                return Direction.Colinear;
            }
            else if (angledir > 0)
            {
                return Direction.Clockwise;
            }
            else
            {
                return Direction.Counterclockwise;
            }
        }

        /// <summary>
        /// Считывает данные из файла
        /// </summary>
        private static void ReadPointsFromFile()
        {
            try
            {
                using (StreamReader sr = new StreamReader(inputPath))
                {
                    int count = int.Parse(sr.ReadLine());
                    points = new List<Point>(count);

                    for (int i = 0; i < count; i++)
                    {
                        string[] xy = sr.ReadLine().Split(' ');
                        points.Add(new Point(int.Parse(xy[0]), int.Parse(xy[1])));
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }

    enum Format
    {
        Plain,
        WellKnownTest
    }

    enum Direction
    {
        Colinear,
        Clockwise,
        Counterclockwise
    }

    class Point
    {
        public int X { get; private set; }

        public int Y { get; private set; }

        public Point(int x, int y)
        {
            X = x;
            Y = y;
        }
    }

    class MyStack
    {
        private readonly List<Point> stack;

        public const int MaxSize = 1000;

        public MyStack(int size)
        {
            stack = new List<Point>(size);
        }

        public bool IsEmpty()
        {
            return stack.Count == 0;
        }

        public int Size()
        {
            return stack.Count;
        }

        public Point Top()
        {
            if (IsEmpty())
            {
                throw new InvalidOperationException();
            }

            return stack[stack.Count - 1];
        }

        public Point NextToTop()
        {
            if (stack.Count < 2)
            {
                throw new InvalidOperationException();
            }

            return stack[stack.Count - 2];
        }

        public Point Pop()
        {
            if (IsEmpty())
            {
                throw new InvalidOperationException();
            }

            Point item = stack[stack.Count - 1];
            stack.Remove(item);

            return item;
        }

        public void Push(Point item)
        {
            if (Size() == MaxSize)
            {
                throw new InvalidOperationException();
            }

            stack.Add(item);
        }
    }
}
