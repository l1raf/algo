namespace CW
{
    public class DimDate
    {
        public int DateKey { get; set; }

        public string FullDateAlternateKey { get; set; }

        public byte DayNumberOfWeek { get; set; }

        public string EnglishDayNameOfWeek { get; set; }

        public byte DayNumberOfMonth { get; set; }

        public short DayNumberOfYear { get; set; }

        public byte WeekNumberOfYear { get; set; }

        public string EnglishMonthName { get; set; }

        public byte MonthNumberOfYear { get; set; }

        public byte CalendarQuarter { get; set; }

        public short CalendarYear { get; set; }

        public byte CalendarSemester { get; set; }

        public byte FiscalQuarter { get; set; }

        public short FiscalYear { get; set; }

        public byte FiscalSemester { get; set; }
    }
}