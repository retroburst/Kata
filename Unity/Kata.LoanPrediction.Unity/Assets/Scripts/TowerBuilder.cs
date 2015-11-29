using UnityEngine;
using System.Collections;
using System.Linq;

public class TowerBuilder : MonoBehaviour {
	public Vector3 TowerBasePosition = new Vector3(0f, 2.5f, 0f);
	public float TowerRoofPosition = 3.0f;
	public GameObject[] TowerWallPrefabs;
	public GameObject TowerBasePrefab;
	public GameObject TowerRoofPrefab;
	
	// Use this for initialization
	void Start () {
		BuildTower(25, true);
	}
	
	public void BuildTower(int levels, bool removeBeforeBuild = true)
	{
		if(removeBeforeBuild) {
			GameObject[] towerBlocks = GameObject.FindGameObjectsWithTag("Tower");
			foreach(GameObject gameObject in towerBlocks) { GameObject.Destroy(gameObject); }
		}
		if(levels <= 0) return;	
		int numWallLevelsNeeded = levels - 1;
		GameObject towerBase = (GameObject)GameObject.Instantiate(TowerBasePrefab, TowerBasePosition, TowerBasePrefab.transform.rotation);
		for(int i=0; i < numWallLevelsNeeded; i++)
		{
			GameObject towerWallPrefab = TowerWallPrefabs[Random.Range(0, TowerWallPrefabs.Length)];
			Vector3 position = new Vector3(towerBase.transform.position.x, towerBase.transform.position.y + ((i + 1) * towerWallPrefab.transform.localScale.y), towerBase.transform.position.z);
			GameObject wall = (GameObject)GameObject.Instantiate(towerWallPrefab, position, towerWallPrefab.transform.rotation);
		}
		Vector3 roofPosition = new Vector3(TowerBasePosition.x, TowerBasePosition.y + ((numWallLevelsNeeded * TowerBasePrefab.transform.localScale.y) + TowerRoofPosition), TowerBasePosition.z);
		GameObject towerRoof = (GameObject)GameObject.Instantiate(TowerRoofPrefab, roofPosition, TowerRoofPrefab.transform.rotation);
	}
}
