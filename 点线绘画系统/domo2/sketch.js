var CircleArr=[];
var WIDTH=710,HEIGHT=400,POINT=0,AddPoint=1;
	
function setup()
 { 
  createCanvas(WIDTH,HEIGHT);
    background(0);
strokeWeight(1);
    CircleArr=[];
for (var i = 0; i < POINT; i++)
{
  
  CircleArr.push(drawCircle(random(WIDTH),random(HEIGHT),random(6,2),random(1/2,-1/2),random(1/2,-1/2)));
}

	 
	 
	 
	 
	 button_1 = createButton('Change add point model');
  button_1.position(WIDTH+19, 30);
  button_1.mousePressed(changeAP);
	 
	 
	 
	 
	 
	 
	 
	 button_2 = createButton('Change background_color model');
	 button_2.position(WIDTH+19, 30*2);
  button_2.mousePressed(changeBC);
	 
	 

	 slider = createSlider(1, 50, 10);
  slider.position(WIDTH+19, 30*3);
  slider.style('width', '200px');

	 
	 checkbox_1 = createCheckbox('Motion is related to mouse position', true);
	 checkbox_1.position(WIDTH+19, 30*4);
  	checkbox_1.changed(myChecked_1Event);
	 
	 checkbox_2 = createCheckbox('Static', false);
	 checkbox_2.position(WIDTH+19, 30*5);
  	checkbox_2.changed(myChecked_2Event);
	 
}



function changeAP() {					//change add point model
  IsmousePressed=-IsmousePressed;
	
}

function changeBC() {					//change add point model
  Color_Is_Relate_to_distance=-Color_Is_Relate_to_distance;
}

function myChecked_1Event()
{
  Motion_Is_Related_to_mouse_position=-Motion_Is_Related_to_mouse_position;
}

function myChecked_2Event()
{
  Is_Static=-Is_Static;
}

var IsmousePressed=1;
var Color_Is_Relate_to_distance=1;
var Motion_Is_Related_to_mouse_position=1;
var Is_Static=-1;


var Roff=0.8;

var Goff=0.8;

var Boff=0.8;

function draw()
 {
   for (var i = 0; i < POINT; i++) 
{
  
var cir=CircleArr[i];
	
	 var W_SDTM,H_SDTM;   //Width_SqrtDistanceToMid
	if(Motion_Is_Related_to_mouse_position==1)
	{
	W_SDTM=sqrt(abs(randomGaussian(mouseY-WIDTH/2,0)));//1-17.4
	H_SDTM=sqrt(abs(randomGaussian(mouseY-HEIGHT/2,0)));//1-14.1
	} //WH=sqrt(W_SDTM*W_SDTM+H_SDTM*H_SDTM);//1.4-22.5
	else
	{
		W_SDTM=2;
		H_SDTM=2;
	}
	
	if(Is_Static==1)
	{
		W_SDTM=0;
		H_SDTM=0;
	}
	
	
	
	
	
	
	if(mouseX-WIDTH/2>0&&Motion_Is_Related_to_mouse_position==1)
	{
cir.x+=cir.moveX*W_SDTM/4;
cir.y+=cir.moveY*H_SDTM/4;
	}
	
	else
	{
	cir.x-=cir.moveX*W_SDTM/4;
	cir.y-=cir.moveY*H_SDTM/4;
	}

	
	
if(cir.x>WIDTH)
cir.x=0;
else if(cir.x<0)
cir.x=WIDTH;

if(cir.y>HEIGHT)
cir.y=0;
else if(cir.y<0)
cir.y=HEIGHT;

}                                 //完成变化量的变化
	 
	 if(Color_Is_Relate_to_distance==1)
	{
		WH=10;
	}
	 else
	 {
		 WH=slider.value();
	 }
	 
	 
	 
	 Roff=Roff+0.001*WH/8;
	 Goff=Goff+0.002*WH/8;
	 Boff=Boff+0.003*WH/8;

background(255*noise(Roff),255*noise(Goff),255*noise(Boff));                  //清屏

 
	 CircleArr.push(drawCircle(mouseX,mouseY,5,random(1/4,-1/4),random(1/4,-1/4)));
POINT=POINT+1;

for (var j = 0; j < POINT; j++)    //画点
{

    var cirr=CircleArr[j];
drawCircle(cirr.x,cirr.y,cirr.r,cirr.moveX,cirr.moveY) 
}
	 
for (var i = 0; i < POINT; i++)    //画线
{
				for (var j = 0; j < POINT; j++)
				{
					if (i + j < POINT)
					{
						var A = abs(CircleArr[i+j].x - CircleArr[i].x),
							B = abs(CircleArr[i+j].y - CircleArr[i].y);
						var lineLength = sqrt(A*A + B*B);
						var C = 1/lineLength*5-0.02;
						var lineOpacity = C > 0.04 ? 0.04 : C;
						if (lineOpacity > 0)
						{
							drawLine(CircleArr[i].x, CircleArr[i].y, CircleArr[i+j].x, CircleArr[i+j].y, lineOpacity);
						}
					}
				}
			}
	 
CircleArr.pop();
POINT=POINT-1;

}






function Line_O(x1,y1,x2,y2,o)
{
	    this.beginX = x1,
			this.beginY = y1,
			this.closeX = x2,
			this.closeY = y2,
			this.o = o;
}

function Circle (x, y, r, moveX, moveY) {
			this.x = x,
			this.y = y,
			this.r = r,
			this.moveX = moveX,
			this.moveY = moveY;
		}

function drawCircle(x,y,r,moveX,moveY)
{
var circle = new Circle(x, y, r, moveX, moveY)

	 noStroke();

color_cir=color(0, 0, 0,0.3*255);
fill(color_cir);
ellipse(x,y,r,r);
	return circle;
}


function drawLine(x1,y1,x2,y2,o)
{
	 
	var line_1 = new Line_O(x1, y1, x2, y2, o)
form = color(0,0,0, 9*o*255);
	stroke(form);
  line(x1, y1, x2, y2);
}

function mouse_IN_canvous()
{
	var IS_in;
	if(mouseX<WIDTH&&mouseX>0&&mouseY<HEIGHT&&mouseY>0)
	{
		IS_in=1;
	}
	else
	{
		IS_in=0;
	}
	return IS_in;
}



function mousePressed() {
	if(IsmousePressed==1&&mouse_IN_canvous())
	{
	for (var j = 0; j < AddPoint; j++) 
	{
CircleArr.push(drawCircle(mouseX,mouseY,random(6,2),random(1/2,-1/2),random(1/2,-1/2)));
	POINT++;
	}
	}
}

function mouseDragged() {
	if(IsmousePressed==-1&&mouse_IN_canvous())
	{
	for (var j = 0; j < AddPoint; j++) 
	{
CircleArr.push(drawCircle(mouseX,mouseY,random(6,2),random(1/2,-1/2),random(1/2,-1/2)));
	POINT++;
	}
	}
}








