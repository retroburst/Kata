﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Kata.LoanPrediction.CSharp.Common.Helpers
{
    /// <summary>
    /// Helpers for enumerations.
    /// </summary>
    public static class EnumerationHelpers
    {
        /// <summary>
        /// Gets the description.
        /// </summary>
        /// <param name="en">The en.</param>
        /// <returns></returns>
        public static string GetDescription(Enum en)
        {
            Type type = en.GetType();
            MemberInfo[] memInfo = type.GetMember(en.ToString());
            if (memInfo != null && memInfo.Length > 0)
            {
                object[] attrs = memInfo[0].GetCustomAttributes(typeof(DescriptionAttribute), false);
                if (attrs != null && attrs.Length > 0)
                {
                    return ((DescriptionAttribute)attrs[0]).Description;
                }
            }
            return (en.ToString());
        }
    }
}
