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
	public float BuildTowerPerBlockDelayInSeconds = 0.1f;
	public GameObject[] TowerWallPrefabs;
	public GameObject TowerBasePrefab;
	public GameObject TowerRoofPrefab;
	public GameObject ExampleTower = null;
	private List<GameObject> cachedTowerWallBlocks = null;
	private GameObject cachedTowerRoofBlock = null;
	private GameObject cachedTowerBaseBlock = null;

	/// <summary>
	/// Awake this instance.
	/// </summary>
	private void Awake()
	{
		cachedTowerWallBlocks = new List<GameObject>();
		if(ExampleTower != null) GameObject.Destroy(ExampleTower);
	}

	/// <summary>
	/// Builds the tower.
	/// </summary>
	/// <returns>The tower.</returns>
	/// <param name="levels">Levels.</param>
	/// <param name="removeBeforeBuild">If set to <c>true</c> remove before build.</param>
	public List<GameObject> BuildTower (int levels, bool removeBeforeBuild = true)
	{
		List<GameObject> towerLevels = new List<GameObject> ();
		StopCoroutine("BuildTowerWithDelay");
		if (removeBeforeBuild) {
			ClearTower ();
		}
		if (levels <= 0){
			return (towerLevels);	
		}
		int numWallLevelsNeeded = levels - 1;
		AddTowerBase (towerLevels);
		AddTowerWalls (towerLevels, numWallLevelsNeeded);
		AddTowerRoof (towerLevels, numWallLevelsNeeded);
		// build the tower with a delay
		StartCoroutine(BuildTowerWithDelay(towerLevels.ToArray()));
		// remove the roof before returning to the caller as 
		// not strictly to be treated as a tower block in calling
		// code
		towerLevels.Remove(cachedTowerRoofBlock);
		return(towerLevels);
	}

	/// <summary>
	/// Adds the tower base.
	/// </summary>
	/// <param name="towerLevels">Tower levels.</param>
	private void AddTowerBase (List<GameObject> towerLevels)
	{
		if (cachedTowerBaseBlock == null) {
			cachedTowerBaseBlock = (GameObject)GameObject.Instantiate (TowerBasePrefab, TowerBasePosition, TowerBasePrefab.transform.rotation);
			cachedTowerBaseBlock.SetActive (false);
		}
		else {
			cachedTowerBaseBlock.transform.position = TowerBasePosition;
			cachedTowerBaseBlock.transform.rotation = TowerBasePrefab.transform.rotation;
			cachedTowerBaseBlock.SetActive (false);
		}
		towerLevels.Add (cachedTowerBaseBlock);
	}

	/// <summary>
	/// Adds the tower walls.
	/// </summary>
	/// <param name="towerLevels">Tower levels.</param>
	/// <param name="numWallLevelsNeeded">Number wall levels needed.</param>
	private void AddTowerWalls (List<GameObject> towerLevels, int numWallLevelsNeeded)
	{
		for (int i = 0; i < numWallLevelsNeeded; i++) {
			Vector3 nextWallPosition = new Vector3 (cachedTowerBaseBlock.transform.position.x, cachedTowerBaseBlock.transform.position.y + ((i + 1) * TowerBasePrefab.transform.localScale.y), cachedTowerBaseBlock.transform.position.z);
			GameObject cachedTowerWallBlock = GetNextRandomCachedTowerBlock ();
			if (cachedTowerWallBlock == null) {
				GameObject towerWallPrefab = TowerWallPrefabs [Random.Range (0, TowerWallPrefabs.Length)];
				cachedTowerWallBlock = (GameObject)GameObject.Instantiate (towerWallPrefab, nextWallPosition, towerWallPrefab.transform.rotation);
			}
			else {
				cachedTowerWallBlock.transform.position = nextWallPosition;
				// pull it out of the cache
				cachedTowerWallBlocks.Remove (cachedTowerWallBlock);
			}
			cachedTowerWallBlock.SetActive (false);
			towerLevels.Add (cachedTowerWallBlock);
		}
	}

	/// <summary>
	/// Adds the tower roof.
	/// </summary>
	/// <param name="towerLevels">Tower levels.</param>
	/// <param name="numWallLevelsNeeded">Number wall levels needed.</param>
	private void AddTowerRoof (List<GameObject> towerLevels, int numWallLevelsNeeded)
	{
		// put the roof on top
		Vector3 roofPosition = new Vector3 (TowerBasePosition.x, TowerBasePosition.y + ((numWallLevelsNeeded * TowerBasePrefab.transform.localScale.y) + TowerRoofPosition), TowerBasePosition.z);
		if (cachedTowerRoofBlock == null) {
			cachedTowerRoofBlock = (GameObject)GameObject.Instantiate (TowerRoofPrefab, roofPosition, TowerRoofPrefab.transform.rotation);
			cachedTowerRoofBlock.SetActive (false);
		}
		else {
			cachedTowerRoofBlock.transform.position = roofPosition;
			cachedTowerRoofBlock.transform.rotation = TowerRoofPrefab.transform.rotation;
			cachedTowerRoofBlock.SetActive (false);
		}
		towerLevels.Add (cachedTowerRoofBlock);
	}

	/// <summary>
	/// Builds the tower with delay.
	/// </summary>
	/// <returns>The tower with delay.</returns>
	/// <param name="tower">Tower.</param>
	private IEnumerator BuildTowerWithDelay(GameObject[] towerLevels)
	{
		for(int i=0; i < towerLevels.Length; i++)
		{
			towerLevels[i].SetActive(true);
			yield return new WaitForSeconds(BuildTowerPerBlockDelayInSeconds);
		}	
	}

	/// <summary>
	/// Clears the tower.
	/// </summary>
	public void ClearTower ()
	{
		// get the walls and clear then re-cache
		GameObject[] towerWallBlocks = GameObject.FindGameObjectsWithTag (Constants.TAG_TOWER_WALL);
		foreach (GameObject gameObject in towerWallBlocks) {
			gameObject.SetActive(false);
			// put the walls back in the cache this will re-use any existing walls from the example tower
			// already in the scene
			cachedTowerWallBlocks.Add(gameObject);
		}
		// get the base, clear and cache
		GameObject towerBaseBlock = GameObject.FindGameObjectWithTag (Constants.TAG_TOWER_BASE);
		if(towerBaseBlock != null)
		{
			towerBaseBlock.SetActive(false);
			// this will re-use the base that is already in the scene as an example tower
			if(cachedTowerBaseBlock == null) cachedTowerBaseBlock = towerBaseBlock;
		}
		// get the roof, clear and cache
		GameObject towerRoofBlock = GameObject.FindGameObjectWithTag (Constants.TAG_TOWER_ROOF);
		if(towerRoofBlock != null)
		{
			towerRoofBlock.SetActive(false);
			// this will re-use the roof that is already in the scene as an example tower
			if(cachedTowerRoofBlock == null) cachedTowerRoofBlock = towerRoofBlock;
		}
	}

	/// <summary>
	/// Gets the next random cached tower block.
	/// </summary>
	/// <returns>The next random cached tower block.</returns>
	private GameObject GetNextRandomCachedTowerBlock()
	{
		if(cachedTowerWallBlocks.Count == 0) return (null);
		int randomIndex = Random.Range(0, cachedTowerWallBlocks.Count);
		return(cachedTowerWallBlocks[randomIndex]);
	}

}
