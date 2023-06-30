using System;

namespace CW
{
    public class DimProduct
    {
        public int ProductKey { get; set; }

        public string ProductAlternateKey { get; set; }

        public string EnglishProductName { get; set; }

        public string Color { get; set; }

        public short SafetyStockLevel { get; set; }

        public short ReorderPoint { get; set; }

        public string SizeRange { get; set; }

        public int DaysToManufacture { get; set; }

        public DateTime StartDate { get; set; }
    }
}