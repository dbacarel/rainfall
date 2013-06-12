#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <assert.h>
#include <vector>
#include <ostream>
#include <iterator>

using namespace std;


struct cell 
{
    unsigned int altitude;
    unsigned int row;
    unsigned int col;
    bool marked;
    int basin_counter;
    unsigned int map_size;
    
   
};

pair<int,int>
getLower(int x,int y, cell** m)
{

    assert(x >=0 && y>=0);
    
    unsigned s = m[x][y].map_size;
    unsigned low_x,low_y;
    unsigned min = m[x][y].altitude;
    
    
    for(unsigned i=0;i<8;i++)
    {
  
	if(y+1 < s && m[x][y+1].altitude < min)
	{
	    low_x = x;
	    low_y = y+1;
	    min= m[x][y+1].altitude;
	    
	}
	
	if(x+1 < s && y+1 < s && m[x+1][y+1].altitude < min)
	{
	    low_x = x+1;
	    low_y = y+1;
	    min = m[x+1][y+1].altitude;
	}
	
	if(x+1 < s && m[x+1][y].altitude < min)
	{
	    low_x = x+1;
	    low_y = y;
	    min = m[x+1][y].altitude;
	}
	
		
	if(x-1 >= 0  && m[x-1][y].altitude < min)
	{
	    low_x = x-1;
	    low_y = y;
	    min = m[x-1][y].altitude;
	    
	}

	if(y-1 >= 0 && m[x][y-1].altitude < min)
	{
	    low_x = x;
	    low_y = y-1;
	    min = m[x][y-1].altitude;

	}
	
	if(x-1 >= 0 && y+1 < s && m[x-1][y+1].altitude < min)
	{
	    low_x = x-1;
	    low_y = y+1;
	    min = m[x-1][y+1].altitude;
	    
	}
	
	if(x-1 >= 0 && y-1 >= 0  && m[x-1][y-1].altitude < min)
	{
	    low_x = x-1;
	    low_y = y-1;
	    min = m[x-1][y-1].altitude;
	    
	}
	
	
	if(x+1 < s && y-1 >= 0 && m[x+1][y-1].altitude < min)
	{
	    low_x = x+1;
	    low_y = y-1;
	    min = m[x+1][y-1].altitude;
	    
	}
	
		 
    }

    
    if(min == m[x][y].altitude)
	return make_pair(-1,-1);
    else
	return make_pair(low_x,low_y);
    

    
    
}


void
partition(unsigned x,unsigned y, cell ** m,int counter)
{
    pair<int,int> next= getLower(x,y,m);
    if(next.first == -1)
    {
	
	
	m[x][y].basin_counter +=  m[x][y].marked ? counter : counter+1;
	m[x][y].marked=true;

	return ;
	 
    }
    
    int next_counter;
    
    next_counter= m[x][y].marked ? counter : counter+1; 
    m[x][y].marked=true;
   
    
    
    
    partition(next.first,next.second, m , next_counter);
    

}

int main(int argc, char** argv)
{
    string s_str, row;    
    
    
    int map_size;
    
    //Reading the map size
    getline(cin, s_str);
    map_size=atoi(s_str.c_str());
  
    cell** map= new cell*[map_size];
    
    for(unsigned i=0;i<map_size;i++)
    {
	map[i] = new cell[map_size];
	getline(cin, row);
	istringstream iss(row);
	
	unsigned col=0;

	do
	{
	    string altitude;
	    iss >> altitude;
	     	    
	    map[i][col].altitude= atoi(altitude.c_str());	   	    
	    map[i][col].row = i;
	    map[i][col].col = col;
	    map[i][col].marked = false;
	    map[i][col].map_size = map_size;
	    map[i][col].basin_counter=0;
	    	    	    
	    col++;	    
	    
	}while(col<map_size);
	
    }
    
    
	
    for(unsigned i=0;i<map_size;i++)
	for(unsigned j=0;j<map_size;j++)
	    if(!map[i][j].marked)
		partition(i,j,map,0);


    vector<int> parts_size;
    int sum=0;
	
	
    for(unsigned i=0;i<map_size;i++)
	for(unsigned j=0;j<map_size;j++) 
	{
	    if(map[i][j].basin_counter>0)
	    {
		sum+=map[i][j].basin_counter;
		    
		parts_size.push_back(map[i][j].basin_counter);
	    }
		
			
	}
	

    assert(sum == map_size*map_size);
    sort(parts_size.rbegin(), parts_size.rend());	 
    copy(parts_size.begin(), parts_size.end(), ostream_iterator<int>(cout, " "));
	
    return 0;
    
}

	
    
