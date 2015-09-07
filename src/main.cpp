#include <iostream>
#include <vector>
#include <cmath>

#define SIZE_X (20)
#define SIZE_Y (35)

void wait(){
    std::cin.ignore();
}

struct Node{
	int x,y;
	int cost, gcost;
	int parent;
};

void draw(char map[][SIZE_Y]){
	for(int i=0; i<SIZE_X; i++){
		for(int j=0; j<SIZE_Y; j++){
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}

int calcCost(int nx, int ny, int ex, int ey){
	float dist = sqrt(pow(nx - ex, 2) + pow(ny - ey, 2));
	return dist*10;
}

int main(){
	
	char map[SIZE_X][SIZE_Y];

	
	for(int i=0; i<SIZE_X; i++){
		for(int j=0; j<SIZE_Y; j++){
			map[i][j] = ' ';
			if (i == 0 || i == SIZE_X-1 ||j == 0 || j == SIZE_Y-1){
				map[i][j] = 'x';
			}
		}
	}
	
	int sx = 2, sy = 5;
	int ex = 15, ey = 15;
	map[sx][sy] = 'S';
	map[ex][ey] = 'E';
	for(int i=0; i<15; i++){
		map[10][i] = 'x';
		map[i][13] = 'x';
	}
	map[5][13] = ' ';
	
	draw(map);
	
	std::vector<Node> nodes;
	Node newNode;
	newNode.x = sx;
	newNode.y = sy;
	newNode.gcost = 0;
	newNode.cost = -1;
	newNode.parent = -1;
	nodes.push_back(newNode);
	
	int end = 0;
	while(end == 0){
		int posx, posy;
		int hcost = 1000, hi = 0;
		for(unsigned int n=0; n<nodes.size(); n++){
			if(nodes[n].cost != -1){
				if (nodes[n].cost < hcost){
					hcost = nodes[n].cost;
					hi = n;
				}
			}
		}
		nodes[hi].cost = -1;
		posx = nodes[hi].x;
		posy = nodes[hi].y;
		for(int i=-1; i<2; i++){
			for(int j=-1; j<2; j++){
				bool makeNew = true;
				if (i == 0 && j == 0){
					makeNew = false;
				}
				for(unsigned int n=0; n<nodes.size(); n++){
					if (nodes[n].x == posx+i && nodes[n].y == posy+j){
						makeNew = false;
						int cost = 0;
						if (i == 0 || j == 0){
							cost = 10;
						} else {
							cost = 14;
						}
						if(nodes[n].gcost > nodes[hi].gcost + cost){
							nodes[n].gcost = nodes[hi].gcost + cost;
							nodes[n].parent = hi;
						}
					}
				}
				if(map[posx+i][posy+j] == 'x'){
					makeNew = false;
				}
				if (makeNew){
					newNode.x = posx+i;
					newNode.y = posy+j;
					newNode.cost = calcCost(newNode.x, newNode.y, ex, ey);
					if (newNode.cost == 0){
						end = nodes.size();
					}
					newNode.parent = hi;
					if (i == 0 || j == 0){
						newNode.gcost = nodes[hi].gcost + 10;
					} else {
						newNode.gcost = nodes[hi].gcost + 14;
					}
					newNode.cost += newNode.gcost;
					nodes.push_back(newNode);
				}
			}
		}
		
		
		int os = 0;
		for(unsigned int n=0; n<nodes.size(); n++){
			if(nodes[n].cost != -1){
				map[nodes[n].x][nodes[n].y] = 'o';
				os++;
			} else {
				map[nodes[n].x][nodes[n].y] = 'O';
			}
		}
		if(os == 0){
			std::cout << "Path cannot be found" << std::endl;
			wait();
			return 0;
		}
		
		//for drawing every step
		//draw(map);
	}
	
	for(int i=0; i<SIZE_X; i++){
		for(int j=0; j<SIZE_Y; j++){
			if(map[i][j] == 'o' || map[i][j] == 'O'){
				map[i][j] = ' ';
			}
		}
	}
	while(nodes[end].parent != -1){
		map[nodes[end].x][nodes[end].y] = 'o';
		end = nodes[end].parent;
	}
	map[nodes[end].x][nodes[end].y] = 'o';
	
	draw(map);
	
	
	wait();
    return 0;
}
