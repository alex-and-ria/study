using UnityEngine;
using System.Collections;

public class camera_controller : MonoBehaviour {
	public GameObject plr;
	private Vector3 ofst;
	void Start(){
		ofst = transform.position - plr.transform.position;
	}
	void LateUpdate(){
		transform.position = plr.transform.position + ofst;
	}
}
