namespace CW
{
    abstract class Bitmap
    {
        public abstract void And(Bitmap other);

        public abstract void Set(uint i, bool value);

        public abstract bool Get(uint i);
    }
}