using System;

namespace CW
{
    public class DimEmployee
    {
        public int EmployeeKey { get; set; }

        public string FirstName { get; set; }

        public string LastName { get; set; }

        public string Title { get; set; }

        public DateTime BirthDate { get; set; }

        public string LoginID { get; set; }

        public string EmailAddress { get; set; }

        public string Phone { get; set; }

        public string MaritalStatus { get; set; }

        public string Gender { get; set; }

        public byte PayFrequency { get; set; }

        public short VacationHours { get; set; }

        public short SickLeaveHours { get; set; }

        public string DepartmentName { get; set; }

        public DateTime StartDate { get; set; }
    }
}