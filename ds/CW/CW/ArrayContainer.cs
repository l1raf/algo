using System;
using System.Collections;

namespace CW
{
    class ArrayContainer : Container, IEnumerable
    {
        private ushort[] values;
        private int cardinality = 0;

        public override int MaxCapacity
        {
            get {
                return 4096;
            }
        }

        public override int Cardinality
        {
            get {
                return cardinality;
            }
        }

        public ArrayContainer() { }

        public ArrayContainer(BitmapContainer bc, int cardinality)
        {
            this.cardinality = cardinality;
            values = new ushort[cardinality];
            bc.FillArray(values);
        }

        public ArrayContainer(int capacity)
        {
            cardinality = capacity;
            if (capacity <= MaxCapacity)
                values = new ushort[capacity];
        }

        public ArrayContainer(ushort[] values)
        {
            cardinality = values.Length;
            this.values = values;
        }

        public void Add(ushort value)
        {
            if (cardinality + 1 <= MaxCapacity)
            {
                if (values == null)
                    values = new ushort[1];
                else
                    Array.Resize(ref values, values.Length + 1);

                values[cardinality] = value;
                cardinality++;
                Array.Sort(values);
            }
        }

        public BitmapContainer ToBitmapContainer()
        {
            return new BitmapContainer(values, cardinality);
        }

        public void Remove(ushort value)
        {
            int index = Contains(value);

            if (index > -1)
            {
                for (int i = index; i < values.Length - 1; i++)
                    values[i] = values[i + 1];

                Array.Resize(ref values, values.Length - 1);
                cardinality--;
            }
        }

        public int Contains(ushort value)
        {
            if (values == null)
                return -1;
            return Array.BinarySearch(values, value);
        }

        public static ArrayContainer operator &(ArrayContainer arrayContainer, BitmapContainer bitmapContainer)
        {
            ArrayContainer answer = new ArrayContainer();

            if (arrayContainer.values == null)
                return new ArrayContainer();

            for (int i = 0; i < arrayContainer.values.Length; i++)
                if (bitmapContainer.Get(arrayContainer.values[i]))
                    answer.Add(arrayContainer.values[i]);

            return answer;
        }

        public static ArrayContainer operator &(BitmapContainer bitmapContainer, ArrayContainer arrayContainer)
        {
            return arrayContainer & bitmapContainer;
        }

        public static ArrayContainer operator &(ArrayContainer ac1, ArrayContainer ac2)
        {
            if (ac1.values == null || ac2.values == null)
                return new ArrayContainer();

            ArrayContainer arrayContainer = new ArrayContainer();

            for (int i = 0; i < ac1.values.Length; i++)
            for (int j = 0; j < ac2.values.Length; j++)
                if (ac1[i] == ac2[j])
                    arrayContainer.Add(ac1[i]);

            return arrayContainer;
        }

        public ushort this[int index]
        {
            get {
                return values[index];
            }
            set {
                values[index] = value;
            }
        }

        public IEnumerator GetEnumerator()
        {
            for (int i = 0; i < cardinality; i++)
                yield return values[i];
        }
    }
}