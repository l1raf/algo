using System;

namespace CW
{
    class BitmapContainer : Container
    {
        private uint[] bits;
        private int cardinality = 0;

        public override int Cardinality
        {
            get {
                return cardinality;
            }
        }

        public uint Count
        {
            get {
                return BitCount(bits);
            }
        }

        public override int MaxCapacity
        {
            get {
                return 1 << 16;
            }
        }

        public BitmapContainer()
        {
            //Резервируем 2 ^ 16 бит
            bits = new uint[1 << 11];
        }

        public BitmapContainer(ushort[] values, int cardinality)
        {
            bits = new uint[1 << 11];
            this.cardinality = cardinality;

            for (int i = 0; i < cardinality; i++)
                Set(values[i], true);
        }

        public ArrayContainer ToArrayContainer()
        {
            return new ArrayContainer(this, cardinality);
        }

        public void FillArray(ushort[] data)
        {
            int pos = 0;

            for (int i = 0; i < bits.Length; i++)
            {
                var bitset = bits[i];

                while (bitset != 0)
                {
                    data[pos++] = (ushort)(i * 32 + (TrailingZeroCount(bitset)));
                    bitset &= (bitset - 1);
                }
            }
        }

        public static int TrailingZeroCount(uint value)
        {
            if (value == 0)
                return 32;

            int count = 0;
            while ((value & 1) == 0)
            {
                value >>= 1;
                count++;
            }

            return count;
        }

        public static Container operator &(BitmapContainer bc1, BitmapContainer bc2)
        {
            int newCardinality = 0;
            int n = Math.Min(bc1.bits.Length, bc2.bits.Length);

            for (int i = 0; i < n; i++)
                newCardinality += (int)BitCount(bc1.bits[i] & bc2.bits[i]);

            if (newCardinality > 4096)
            {
                BitmapContainer bitmapContainer = new BitmapContainer();

                for (int i = 0; i < bitmapContainer.bits.Length; i++)
                    bitmapContainer.bits[i] = bc1.bits[i] & bc2.bits[i];

                bitmapContainer.cardinality = newCardinality;

                return bitmapContainer;
            }
            else
            {
                ArrayContainer arrayContainer = new ArrayContainer(newCardinality);
                FillArray(arrayContainer, bc1.bits, bc2.bits);

                return arrayContainer;
            }
        }

        public static void FillArray(ArrayContainer arrayContainer, uint[] bits1, uint[] bits2)
        {
            int pos = 0;

            for (int i = 0; i < bits1.Length; i++)
            {
                uint bitset = bits1[i] & bits2[i];

                while (bitset != 0)
                {
                    arrayContainer[pos++] = (ushort)(i * 32 + TrailingZeroCount(bitset));
                    bitset &= (bitset - 1);
                }
            }
        }

        public static uint BitCount(uint x)
        {
            x -= ((x >> 1) & 0x55555555u);
            x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
            return (((x + (x >> 4)) & 0x0F0F0F0Fu) * 0x01010101u) >> 24;
        }

        public static uint BitCount(uint[] data)
        {
            uint result = 0;
            for (int i = 0; i < data.Length; i++)
                result += BitCount(data[i]);
            return result;
        }

        public bool Get(int i)
        {
            int offset = i >> 5;
            if (offset >= bits.Length)
                return false;
            return (bits[offset] & (1 << i)) != 0;
        }

        public void Set(int i, bool value)
        {
            int offset = i >> 5;

            if (value)
            {
                bits[offset] |= (uint)1 << i;
                cardinality++;
            }
            else
            {
                bits[offset] &= ~((uint)1 << i);
                cardinality--;
            }
        }
    }
}