using System;

namespace CW
{
    class RoaringBitmap : Bitmap
    {
        private Container[] containers;

        public RoaringBitmap()
        {
            containers = new Container[1];
            containers[0] = new ArrayContainer();
        }

        public override void And(Bitmap other)
        {
            int pos1 = 0;
            int pos2 = 0;
            RoaringBitmap rb = other as RoaringBitmap;

            while (pos1 < containers.Length && pos2 < rb.containers.Length)
            {
                Container c1 = containers[pos1];
                Container c2 = rb.containers[pos2];

                Container answer = c1 & c2;
                containers[pos1] = answer;

                pos1++;
                pos2++;
            }
        }

        public override bool Get(uint i)
        {
            int containerIndex = (int)i >> 16;

            if (containers.Length - 1 >= containerIndex && containers[containerIndex] != null)
            {
                if (containers[containerIndex] is BitmapContainer bitmapContainer)
                    return bitmapContainer.Get((int)(i & 0xFFFF));
                else
                    return ((ArrayContainer)containers[containerIndex]).Contains((ushort)(i & 0xFFFF)) >= 0;
            }
            else
            {
                return false;
            }
        }

        public override void Set(uint i, bool value)
        {
            int containerIndex = (int)i >> 16;

            if (containerIndex >= containers.Length)
                Array.Resize(ref containers, containerIndex + 1);

            if (containers[containerIndex] == null)
                containers[containerIndex] = new ArrayContainer();

            if (containers[containerIndex] is ArrayContainer arrayContainer)
            {
                if (value)
                {
                    arrayContainer.Add((ushort)(i & 0xFFFF));

                    if (arrayContainer.Cardinality == 4096)
                        containers[containerIndex] = arrayContainer.ToBitmapContainer();
                }
                else
                {
                    if (arrayContainer.Cardinality != 0)
                        arrayContainer.Remove((ushort)(i & 0xFFFF));
                }
            }
            else
            {
                BitmapContainer bitmapContainer = containers[containerIndex] as BitmapContainer;

                bitmapContainer.Set((int)(i & 0xFFFF), value);

                if (bitmapContainer.Cardinality == 4096)
                    containers[containerIndex] = bitmapContainer.ToArrayContainer();
            }
        }
    }
}