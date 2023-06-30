namespace CW
{
    abstract class Container
    {
        public abstract int Cardinality { get; }

        public abstract int MaxCapacity { get; }

        public static Container operator &(Container c1, Container c2)
        {
            if (c1 is BitmapContainer && c2 is BitmapContainer)
                return ((BitmapContainer)c1) & ((BitmapContainer)c2);
            else if (c1 is ArrayContainer && c2 is ArrayContainer)
                return ((ArrayContainer)c1) & ((ArrayContainer)c2);
            else if (c1 is ArrayContainer && c2 is BitmapContainer)
                return ((ArrayContainer)c1) & ((BitmapContainer)c2);
            else
                return ((ArrayContainer)c2) & ((BitmapContainer)c1);
        }
    }
}