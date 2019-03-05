using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;


public class SetupLocalPlayer : NetworkBehaviour {

    [SyncVar]
    public string pname = "player";

    private float timer = 60.0f;                    //时间控制
    public string GUIname = "player";

    public int display_health;
    public int display_count;
    public bool display_dead;


    [SyncVar]
    public Color playerColor = Color.blue;



    void OnGUI()
    {
        if (isLocalPlayer)
        {
            
              GUIname = GUI.TextField(new Rect(25, Screen.height - 40, 100, 30), GUIname);

            display_health = GetComponent<health>().currentHealth;
            display_count = GetComponent<health>().count;

            display_dead = GetComponent<health>().dead;

            // a= GameObject.FindWithTag"Player"

            //GetComponent<Pi>().
            GUI.Label(new Rect(220, Screen.height - 40, 150, 30), "携带松果数目："+ display_count);

            GUI.Label(new Rect(380, Screen.height - 40, 100, 30), "当前生命值：" + display_health);

            GUI.Label(new Rect(580, Screen.height - 40, 100, 30), "按E吃下松果" );


            if(timer>20.0f)
            GUI.Label(new Rect(Screen.width*0.5f,  10, 180, 200), "距离冬天还有："+(int)(timer-20.0f)+"s");
            else if (timer > 0.0f)
             GUI.Label(new Rect(Screen.width * 0.5f, 10, 180, 200), "距离冬天结束还有：" + (int)(timer) + "s");
            else if(!display_dead)
                GUI.Label(new Rect(Screen.width * 0.5f, 20, 180, 200), "成功度过了冬天，目前存活" + (int)(60.0f - timer) + "s");




            if (display_dead)
            {
                GUI.Label(new Rect(Screen.width * 0.5f, 20, 180, 400), "You Died!游戏结束,你存活了" + (int)(60.0f - timer) + "s");
                Destroy(gameObject);
            }


            if (GUI.Button(new Rect(130,Screen.height - 40, 80, 30), "Change"))
            {
                pname = GUIname;
                CmdChangeName(pname);
            }
        }
    }

    [Command]
    public void CmdChangeName(string newname)
    {
        pname = newname;

    }




    void Start ()

    {
        if (isLocalPlayer)
        {
            GetComponent<drive>().enabled = true;
            Camera.main.transform.position = this.transform.position - this.transform.forward * 20 + this.transform.up * 5;
            Camera.main.transform.LookAt(this.transform.position);
            Camera.main.transform.parent = this.transform;
        }

             Renderer[] rends = GetComponentsInChildren<Renderer>();
            foreach (Renderer r in rends)
                r.material.color = playerColor;

       
           
		
	}


    void OnCollisionEnter(Collision collision)                  //玩家互相伤害，每下扣10点  
    {

        if (collision.gameObject.CompareTag("Player"))
        {

            var hit = collision.gameObject;

            var counttt = hit.GetComponent<health>();

            counttt.TakeplayerDamage(10);                   //玩家互相伤害，每下扣10点
        }
    }




    float i_time_count = 0.5f;

    void Update()
    {

        this.GetComponentInChildren<TextMesh>().text = pname;

        if (isLocalPlayer)
        {
            if (Input.GetKeyDown(KeyCode.E))                //按E键吃松果
            {
                var heal = GetComponent<health>();
                heal.CmdEat();
            }
        }

        //if (Input.GetKeyDown(KeyCode.Q))
        //{
        //    var heal = GetComponent<health>();
        //    heal.TakeDamage(20);
        //}

        if (display_dead!=true)                          //没有dead
        { 
                                     //time为倒计时
        
            timer -= Time.deltaTime;
        
        }



        if (i_time_count >= 0.5)                      //冬天以后，，，实现每半秒触发一次环境伤害
        {
            i_time_count = 0;                       //实现每半秒触发一次

            

                if (timer < 20)
                {
                    var heal = GetComponent<health>();
                    heal.TakeDamage(5);

                }

           
        }









        i_time_count += Time.deltaTime;             //实现每半秒触发一次

    }





 }
