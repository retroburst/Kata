using UnityEngine;
using System.Collections;

/// <summary>
/// Application constants.
/// </summary>
public class Constants
{
	public static readonly string[] DateFormatsForParsing = new string[] { 
		"dd/MM/yyyy",
		"d/M/yyyy",
		"d/MM/yyyy",
		"dd/M/yyyy"
	};

	public const string CHILD_MONTH_BALANCE_TEXT = "MonthBalanceText";
	public const string CHILD_MONTH_TRANSACTIONS_TEXT = "TransactionsText";
	public const string CHILD_WOODEN_SIGN = "WoodenSign";

	public const string TAG_TOWER_BASE = "TowerBase";
	public const string TAG_TOWER_ROOF = "TowerRoof";
	public const string TAG_TOWER_WALL = "TowerWall";

	public const string AXIS_VERTICAL = "Vertical";
}
