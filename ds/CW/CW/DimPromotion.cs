using System;

namespace CW
{
    public class DimPromotion
    {
        public int PromotionKey { get; set; }

        public int PromotionAlternateKey { get; set; }

        public string EnglishPromotionName { get; set; }

        public string EnglishPromotionType { get; set; }

        public string EnglishPromotionCategory { get; set; }

        public DateTime StartDate { get; set; }

        public DateTime EndDate { get; set; }

        public int MinQty { get; set; }
    }
}