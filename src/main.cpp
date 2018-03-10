#include "main.h"
#include "timer.h"
#include "sea.h"
#include "boat.h"
#include "objects.h"
#include "monster.h"
#include "billboard.h"
#include "boss.h"
#include "tower.h"
#include "man.h"


using namespace std;

GLMatrices Matrices;
GLuint     ProgramID,textureProgramID;
GLFWwindow *window;

// Only for barrel
GLuint textureID;	
/**************************
* Customizable functions *
**************************/
#define num_barrels 10
#define num_rocks 300
#define wavetime 1000

Monster monsters;
Boat boat;
Sea sea,sky;
vector<Sphere> sphere;
vector<CubeTextured> barrels;
CubeTextured rocks[num_rocks];
Boss boss;
Cube test_cube;
Tower tower;
Man man;

VerticalRectangle north_wall,south_wall,east_wall,west_wall;


int boat_health = -20,score = -600;
float screen_zoom = 2.0, screen_center_x = 0, screen_center_y = 0, screen_center_z;
float eye_x,eye_y,eye_z;
float target_x,target_y,target_z;
float camera_rotation_angle = 95.0;
// Check which camera view is present
bool camera_follower = true,camera_top_view=false,camera_tower = false,camera_fps=false,camera_helicopter=false;
// Check if click or not
bool clk = false;
// Sphere hold to check whether fireball is on the boat
// boost to activate boost once provided in a gift
bool sphere_hold = false, boost_use = false,pause=false;
int boost = 1;


// Wind Oscillations
float wind = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {


	// All Camera Positions defined here.
	if (camera_follower == true){
		target_x = boat.position.x;
		target_y = boat.position.y;
		target_z = boat.position.z;
		camera_rotation_angle = -boat.rotation + 95;


		eye_x = target_x + 15*cos(camera_rotation_angle*M_PI/180.0f);
		eye_y = target_y + 15;
		eye_z = target_z + 15*sin(camera_rotation_angle*M_PI/180.0f);


	}

	else if (camera_top_view == true){
		target_x = boat.position.x;
		target_y = boat.position.y;
		target_z = boat.position.z;


		eye_x = target_x + 15*cos(camera_rotation_angle*M_PI/180.0f);
		eye_y = target_y + 30;
		eye_z = target_z + 15*sin(camera_rotation_angle*M_PI/180.0f);

	}

	else if (camera_tower == true){
		target_x = boat.position.x;
		target_y = boat.position.y;
		target_z = boat.position.z;


		eye_x = -40;
		eye_y = 70;
		eye_z = -40;

	}

	else if(camera_fps == true){
		camera_rotation_angle = -boat.rotation ;

		target_x = boat.position.x + 15.0f*sin(camera_rotation_angle*M_PI/180.0f);
		target_y = boat.position.y;
		target_z = boat.position.z - 15.0f*cos(camera_rotation_angle*M_PI/180.0f);


		eye_x = boat.position.x + 4.0f*sin(camera_rotation_angle*M_PI/180.0f);
		eye_y = boat.position.y + 5.0f;
		eye_z = boat.position.z - 4.0f*cos(camera_rotation_angle*M_PI/180.0f);


	}


	else if(camera_helicopter == true){


		target_x = 0.0f;
		target_y = 0.0f;
		target_z = 0.0f;
		// camera_rotation_angle = -boat.rotation + 95;

		// eye_x += target_x;
		// eye_z += 10.f;
		mouseuse(window,1600,1600,&eye_x,&eye_z);

		eye_y =  20;


	}

	else
		printf("No camera View Selected\n");



	// clear the color and depth in the frame buffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the loaded shader program
	// Don't change unless you know what you are doing

	// Eye - Location of camera. Don't change unless you are sure!!
	glm::vec3 eye (eye_x,eye_y,eye_z);
	// Target - Where is the camera looking at.  Don't change unless you are sure!!
	glm::vec3 target (target_x, target_y, target_z);
	// Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
	glm::vec3 up (0, 1, 0);

	// Compute Camera matrix (view)
	Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
	// Don't change unless you are sure!!
	// Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

	// Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
	// Don't change unless you are sure!!
	glm::mat4 VP = Matrices.projection * Matrices.view;

	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// For each model you render, since the MVP will be different (at least the M part)
	// Don't change unless you are sure!!
	glm::mat4 MVP;  // MVP = Projection * View * Model

	// Scene render
	sea.draw(VP);
	boat.draw(VP);
	monsters.draw(VP);
	// man.draw(VP);

	vector<Sphere> :: iterator s;
	for (s = sphere.begin(); s < sphere.end(); ++s)
		s->draw(VP);

	vector<CubeTextured> :: iterator b;
	for (b = barrels.begin(); b < barrels.end(); ++b)
		b->draw(VP);

	for (int i = 0; i < num_rocks; ++i)
		rocks[i].draw(VP);

	sky.draw(VP);
	boss.draw(VP);

	north_wall.draw(VP);
	south_wall.draw(VP);
	east_wall.draw(VP);
	west_wall.draw(VP);

	tower.draw(VP);



	// test_cube.draw(VP);

	
}

void tick_input(GLFWwindow *window) {

	// Developer keys
	int left  = glfwGetKey(window, GLFW_KEY_LEFT);
	int right = glfwGetKey(window, GLFW_KEY_RIGHT);
	int up    = glfwGetKey(window, GLFW_KEY_UP);
	int down    = glfwGetKey(window, GLFW_KEY_DOWN);

	// Boat movement 
	int a   = glfwGetKey(window, GLFW_KEY_A);
	int s   = glfwGetKey(window, GLFW_KEY_S);
	int d   = glfwGetKey(window, GLFW_KEY_D);
	int w   = glfwGetKey(window, GLFW_KEY_W);
	int space = glfwGetKey(window, GLFW_KEY_SPACE);
	// Fireballs
	int f   = glfwGetKey(window, GLFW_KEY_F);
	// boost
	int b   = glfwGetKey(window, GLFW_KEY_B);

	// Toggle sail
	int e   = glfwGetKey(window, GLFW_KEY_E);


	// Camera Views
	int t   = glfwGetKey(window, GLFW_KEY_T);
	int u   = glfwGetKey(window, GLFW_KEY_U);
	int y   = glfwGetKey(window, GLFW_KEY_Y);
	int i   = glfwGetKey(window, GLFW_KEY_I);
	int h   = glfwGetKey(window, GLFW_KEY_H);

	if(left){
		camera_rotation_angle +=1;
		
	}


	if(right){

		camera_rotation_angle -=1;
		
	}


	if(up){
		boat.man.plank[2].position.y += 0.1;
	}


	if(down){
		boat.man.plank[2].position.y -= 0.1;
	}


	if(w){
		if(boat.speed > -10.f) 
			boat.speed -= 0.005;
		if(boat.speed > 0)
			boat.speed -= 0.02;

	}

	else if(s){
		if(boat.speed < 10.f) 
			boat.speed += 0.005;
		if(boat.speed < 0)
			boat.speed += 0.02;

	}

	else {
		if (boat.speed < 0) {
			boat.speed += 0.002;
		}
		else if (boat.speed > 0) {
			boat.speed -= 0.002;
		}
		else {
			boat.speed = 0;
		}
	}




	if(a){
		boat.rotation +=1;
	}

	if(d){
		boat.rotation -=1;
	}

	if(e && sphere_hold==false){
		sphere_hold = true;
		boat.sail_on = !boat.sail_on;
	}



	if(t){
		camera_top_view = true;
		camera_follower = false;
		camera_tower = false;
		camera_fps = false;
		camera_helicopter = false;

	}

	if(u){
		camera_follower = true;
		camera_top_view = false;
		camera_tower = false;
		camera_fps = false;
		camera_helicopter = false;


	}

	if(y){
		camera_tower = true;		
		camera_follower = false;
		camera_top_view = false;
		camera_fps = false;
		camera_helicopter = false;

	}

	if(i){
		camera_fps = true;
		camera_tower = false;		
		camera_follower = false;
		camera_top_view = false;
		camera_helicopter = false;
	}

	if(h){
		camera_helicopter = true;
		camera_fps = false;
		camera_tower = false;		
		camera_follower = false;
		camera_top_view = false;
	}


	if(f && sphere_hold == false){


		pthread_t cannon_sound;
		char cannon_filename[] = "../assets/fireball_shoot.mp3"; 
		pthread_create(&cannon_sound,NULL,play_audio,(void*)cannon_filename); 

		sphere_hold = true;
		Sphere new_sphere = Sphere( boat.position.x ,boat.position.y + 3,boat.position.z -1, COLOR_BLACK);
		new_sphere.speed = 1.0f - boat.speed;
		new_sphere.yspeed = 0.05f;
		new_sphere.rotation = -boat.rotation;

		sphere.push_back(new_sphere);
	}

	if(space && boat.jumping == false){
		boat.jumping = true;
		boat.yspeed = 0.4f;
	}


	// Boost 
	if(b && boost > 0 && boost_use == true)
	{
		boost_use = false;
		boost--;
		boat.speed *= 2;
		boat.yspeed += 0.3f;
	}


}

void tick_elements() {


	monsters.tick(boat.position.x, boat.position.z);

	// Check if boss killled
	if(boss.tick(boat.position.x,boat.position.y,boat.position.z))
	{
		pthread_t monster_hit;
		char monster_filename[] = "../assets/monster.mp3"; 
		pthread_create(&monster_hit,NULL,play_audio,(void*)monster_filename);
		// Celebrate defeating boss
		get_gift();
		get_gift();
		get_gift();

		score += 500;
		boat_health += 20;

	}
	
	boat.tick(wind);
	sea.tick();

	// Move each ball and erase them if they have reached the bottom
	vector<Sphere> :: iterator s;
	for (s = sphere.begin(); s < sphere.end(); ++s)
		if(s->tick())
			sphere.erase(s);

	// sea.set_position(boat.position.x,boat.position.z);


}


void collision_function(){

	// if(detect_collision(boat.bounding_box(),sphere1.bounding_box()))
	//     printf("FireBall on the ship\n");
	// else
	//     printf("Fireball flying\n");


	// Check Monster collision with boat
	if(boss.alive && detect_collision(boat.bounding_box(),boss.bounding_box()))
		{
			boat_health = 0;
			printf("Snake attacked:%d\n",score);
		}

	// Check collision with Tower
	if(detect_collision(boat.bounding_box(),tower.bounding_box()))
	{
			boat.on_water = boat.position.y - (int)boat.position.y%10;
			// printf("%lf %lf\n", boat.on_water,boat.position.y);
			if((boat.position.z - tower.position.z)*(boat.position.z - tower.position.z) + (boat.position.x - tower.position.x)*(boat.position.x - tower.position.x) < (130 - boat.on_water - boat.position.y)*(130 - boat.on_water - boat.position.y))
				// On the tower
				if(boat.speed <=0)
					boat.speed += 0.05;
				else if(boat.speed >=0)
					boat.speed -= 0.05;
				else{}	
			else if((boat.position.z - tower.position.z)*(boat.position.z - tower.position.z) + (boat.position.x - tower.position.x)*(boat.position.x - tower.position.x) > (130 - boat.on_water - boat.position.y)*(130 - boat.on_water - boat.position.y))
				boat.on_water -=10;
	}

	else
		boat.on_water = 0.0;




	// Collision with Barrels 
	vector <CubeTextured> ::iterator bar;
	for(bar = barrels.begin(); bar < barrels.end(); bar++)
	if(detect_collision(boat.bounding_box(),bar->bounding_box()))
		{

			printf("Playing sound\n");
			pthread_t barrel_hit;
			char barrel_filename[] = "../assets/barrel.mp3"; 
			pthread_create(&barrel_hit,NULL,play_audio,(void*)barrel_filename); 

			score += 10;
			printf("Hit a Barrel Score:%d\n",score);
			barrels.erase(bar);
			get_gift();
		}


	vector <Prism> :: iterator it;
	for(it = monsters.prism.begin(); it < monsters.prism.end(); it++)
	{
		if(detect_collision(boat.bounding_box(),it->bounding_box()))
		{   
			boat_health -= 10;
			score += 100;
			monsters.kill(it);
			printf("Monster Attack. Health:%d Score:%d\n",boat_health,score);
		 }

	}

	vector <Sphere> :: iterator s;
	for(s = sphere.begin(); s < sphere.end(); ++s)
	{
		for(it = monsters.prism.begin(); it < monsters.prism.end(); it++)
		if(detect_collision(s->bounding_box(),it->bounding_box()))
			{
				pthread_t monster_hit;
				char monster_filename[] = "../assets/monster.mp3"; 
				pthread_create(&monster_hit,NULL,play_audio,(void*)monster_filename); 

				score += 100;
				printf("Fireball Hit Score:%d\n",score);
				monsters.kill(it);
				get_gift();
			}

	// Collision with rocks
		for (int i = 0; i < num_rocks; ++i)
		if(detect_collision(s->bounding_box(),rocks[i].bounding_box()))
			{
			
				printf("Fireball Hit Rock:%d\n",score);
				s->speed = -0.5*(s->speed);
				// Update values so no more detect collision
				for(int t = 0;t<100;i++)
				if(detect_collision(s->bounding_box(),rocks[i].bounding_box()))
					s->tick();
				else 
					break;

				printf("speed:%lf location_x:%lf location_z:%lf\n",s->speed,s->position.x - rocks[i].position.x,s->position.z - rocks[i].position.z );

			}
			
		// No gifts if fireball hits the barrels
		for(bar = barrels.begin(); bar < barrels.end(); bar++)
		if(detect_collision(s->bounding_box(),bar->bounding_box()))
			{
				score += 10;
				printf("Fireball hit Barrel Score:%d\n",score);
				barrels.erase(bar);
			}		

		if(boss.alive && detect_collision(s->bounding_box(),boss.bounding_box()))
		{
			printf("Boss hit\n");
			boss.health -= 25;
			score += 10;

		}


	}

	// Rock Collision
	// With Boat
	for (int i = 0; i < num_rocks; ++i)
	if(detect_collision(boat.bounding_box(),rocks[i].bounding_box()))
		{
			printf("Hit Rock Bottom\n");
				// Update values so no more detect collision
			boat.speed = -0.5*boat.speed;
			for(int t = 0;t<100;i++)
				if(detect_collision(boat.bounding_box(),rocks[i].bounding_box()))
					boat.tick(wind);
				else 
					break;

			printf("speed:%lf location_x:%lf location_z:%lf\n",boat.speed,boat.position.x - rocks[i].position.x,boat.position.z - rocks[i].position.z );
			boat_health -= 5;
		}


}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
	/* Objects should be created before any other gl function and shaders */
	// Create the models

	boat       = Boat(0, 0, COLOR_ORANGE);
	man 		= Man(0,0,COLOR_BROWN);
	
	monsters    = Monster(COLOR_SHARK_FIN);

    GLuint seaTextureID = createTexture("../images/sea1.jpg");
	sea        = Sea( 0, 0, seaTextureID);
    GLuint skyTextureID = createTexture("../images/sky.png");
	sky        = Sea( 0, 400, skyTextureID);

	boss 		= Boss(0,-5,COLOR_SHARK_FIN);

	tower 		= Tower(-40,-40,COLOR_BROWN);

	test_cube = Cube(0,5,0,1,1,1,COLOR_BLUE);


    GLuint sun_textureID = createTexture("../images/right.png");
	north_wall = VerticalRectangle(0,-1000,sun_textureID);
    GLuint wall_textureID = createTexture("../images/left1.png");
	south_wall = VerticalRectangle(0,1000,wall_textureID);
	west_wall = VerticalRectangle(1000,0,wall_textureID);
	west_wall.rotation = -90;
	east_wall = VerticalRectangle(-1000,0,wall_textureID);
	east_wall.rotation = 90;


	// Barrels
    textureID = createTexture("../images/barrel.jpg");
	for(int i=0;i<num_barrels;i++)
		barrels.push_back(CubeTextured(rand()%500 -250,2,rand()%500 -250,10,5,5,textureID));

	// Rocks
    GLuint rockTextureID = createTexture("../images/rock.jpg");

	for (int i = 0; i < num_rocks; ++i)
		rocks[i] = CubeTextured(5*(rand()%500 -250),0,5*(rand()%500 -250),rand()%30 + 10,rand()%30 ,rand()%30+ 10,rockTextureID);


	textureProgramID = LoadShaders( "TextureRender.vert", "TextureRender.frag" );
	Matrices.TexMatrixID = glGetUniformLocation(textureProgramID, "MVP");



	// Create and compile our GLSL program from the shaders
	ProgramID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
	// Get a handle for our "MVP" uniform
	Matrices.MatrixID = glGetUniformLocation(ProgramID, "MVP");


	reshapeWindow (window, width, height);

	// Background color of the scene
	glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
	glClearDepth (1.0f);

	glEnable (GL_DEPTH_TEST);
	glDepthFunc (GL_LEQUAL);

	cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
	cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
	cout << "VERSION: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv) {
	srand(time(0));
	int width  = 1600;
	int height = 1600;


	window = initGLFW(width, height);


	initGL (window, width, height);

	// Get fonts for billboard
	initText2D();


	// Start the audio remix
	pthread_t background_sound;

	char sound_filename[] = "../assets/background.mp3"; 
	pthread_create(&background_sound,NULL,play_audio,(void*)sound_filename); 

	// Check for opengl error
	

	/* Draw in loop */
	for (int t=1;!glfwWindowShouldClose(window);) {
		// Process timers

		if (t60.processTick() && !pause) {
			// 60 fps
			// OpenGL Draw commands
			if(boat_health <= 0)
				{
					boat.set_position(rand()%200,rand()%200);
					boat_health = 100;
				}

			
			// Time for things to recharge
			if(t%50 == 0)
			{	
				sphere_hold = false;
				boost_use = true;
			}



			if(t%wavetime == 0)
			{	
				wind = rand()%180;

				// Create the boss
				if(t%(3*wavetime) == 0 && !boss.alive)
					{boss.alive = true;
					boss.health = 200;
					boss.speed = 0.05*(float)t/wavetime;
					boss.set_position(boat.position.x + 500,boat.position.z - 500 );
					}

				else if(!boss.alive)	
				{
				monsters.add_enemy(t/100,boat.position.x, boat.position.z,COLOR_SHARK_FIN);
				for(int i=0;i<t/200;i++)
					barrels.push_back(CubeTextured(rand()%500 -250,2,rand()%500 -250,10,5,5,textureID));
				}

			}




			draw();

			display_score(t);
			// Print the scoreboard
			// Swap Frame Buffer in double buffering
			glfwSwapBuffers(window);

			// All elements update 
			tick_elements();

			// Collision Engine
			collision_function();

			// Take input from user
			tick_input(window);
			
			reshapeWindow (window, width, height);

		// For stable time flow we update time here
		t++;
		}

		// Poll for Keyboard and mouse events
		glfwPollEvents();
	}

	cleanupText2D();


	quit(window);

	pthread_join(background_sound, NULL);

}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
	return (abs(a.x - b.x) * 2 <= (a.width + b.width)) &&
		   (abs(a.y - b.y) * 2 <= (a.height + b.height)) &&
		   (abs(a.z - b.z) * 2 <= (a.depth + b.depth));


}

void get_gift(){
	int ind = rand()%3;
	// 3 types of gift

	// Get health 
	if(ind == 0)
		{
			boat_health += 10;
			printf("Health increased:%d\n",boat_health);

		}

	// 
	else if (ind == 1)
		{
			score += 50;
			printf("Score Bonus:%d\n",score);

		}		

	else{
		printf("Boost Received\n");
		boost++;
		
	}	

}


void display_score(int time){

	char text[100];

	if(boss.alive)
	{
		sprintf(text," Boss:%d",boss.health);
		printText2D(text, 50, 100, 50);
	}

	else
	{

		time = time%wavetime;
		if(time > wavetime -100)
			printText2D("  !!Incoming!!  ", 50, 100, 50);	

		else{
		sprintf(text,"Score:%d Health:%d Boost:%d",score,boat_health,boost);
		printText2D(text, 50, 50, 25);
		}

	}

}