using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class player_controller : MonoBehaviour {
	private Rigidbody rb;
	private uint cntc;
	private uint cntw;
	public float sd;
	public float tmout;
	public Text cntc_txt;
	public Text cntw_txt;
	public Text win_txt;
	void Start(){
		rb = GetComponent<Rigidbody> ();
		cntc = 0;
		cntw = 0;
		cntctf ();
		win_txt.text = "";
		cntw_txt.text = "";
	}
	void FixedUpdate(){
		float mvh=Input.GetAxis("Horizontal");
		float mvv=Input.GetAxis("Vertical");
		Vector3 mvnt = new Vector3 (mvh, 0.0f, mvv);
		rb.AddForce (mvnt*sd);
	}
	void OnTriggerEnter(Collider othr){
		if (othr.gameObject.CompareTag ("pick_up")) {
			othr.gameObject.SetActive (false);
			++cntc;
			cntctf ();
		}
	}
	void cntctf(){
		cntc_txt.text = "cubes :" + cntc.ToString ();
		cntw_txt.text = "b_wall :" + cntw.ToString ();
		if(cntc>=7) win_txt.text=" 7+ cubs";
	}
	void OnCollisionEnter(Collision clsn){
		Debug.Log("p_enter");
		if (clsn.gameObject.CompareTag ("wall")) {
			++cntw;
			cntctf ();
		}
	}
	void Update(){
		//Debug.Log("time"+Time.fixedTime.ToString());
		if (cntw==4||Time.fixedTime>=tmout) {
			Debug.Log("quit");
			Application.Quit ();
		}
	}
}
