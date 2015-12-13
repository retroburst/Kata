using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

/// <summary>
/// Builds the tower in the application world space.
/// </summary>
public class TowerBuilder : MonoBehaviour
{
	public Vector3 TowerBasePosition = new Vector3 (0f, 2.5f, 0f);
	public float TowerRoofPosition = 3.0f;
	public GameObject[] TowerWallPrefabs;
	public GameObject TowerBasePrefab;
	public GameObject TowerRoofPrefab;

	/// <summary>
	/// Builds the tower.
	/// </summary>
	/// <returns>The tower.</returns>
	/// <param name="levels">Levels.</param>
	/// <param name="removeBeforeBuild">If set to <c>true</c> remove before build.</param>
	public List<GameObject> BuildTower (int levels, bool removeBeforeBuild = true)
	{
		List<GameObject> towerLevels = new List<GameObject> ();
		if (removeBeforeBuild) {
			ClearTower ();
		}
		if (levels <= 0)
			return (towerLevels);	

		int numWallLevelsNeeded = levels - 1;
		GameObject towerBase = (GameObject)GameObject.Instantiate (TowerBasePrefab, TowerBasePosition, TowerBasePrefab.transform.rotation);
		towerLevels.Add (towerBase);
		for (int i = 0; i < numWallLevelsNeeded; i++) {
			GameObject towerWallPrefab = TowerWallPrefabs [Random.Range (0, TowerWallPrefabs.Length)];
			Vector3 position = new Vector3 (towerBase.transform.position.x, towerBase.transform.position.y + ((i + 1) * towerWallPrefab.transform.localScale.y), towerBase.transform.position.z);
			GameObject wall = (GameObject)GameObject.Instantiate (towerWallPrefab, position, towerWallPrefab.transform.rotation);
			towerLevels.Add (wall);
		}
		// put the roof on top
		Vector3 roofPosition = new Vector3 (TowerBasePosition.x, TowerBasePosition.y + ((numWallLevelsNeeded * TowerBasePrefab.transform.localScale.y) + TowerRoofPosition), TowerBasePosition.z);
		GameObject.Instantiate (TowerRoofPrefab, roofPosition, TowerRoofPrefab.transform.rotation);
		return(towerLevels);
	}

	/// <summary>
	/// Clears the tower.
	/// </summary>
	public void ClearTower ()
	{
		GameObject[] towerBlocks = GameObject.FindGameObjectsWithTag (Constants.TAG_TOWER);
		foreach (GameObject gameObject in towerBlocks) {
			GameObject.Destroy (gameObject);
		}
	}
}
