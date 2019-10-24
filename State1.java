
public class State implements Comparable<State>{
    int[][] arr; 
	int level;
	State parent;
	static State goal;
    
	public State()
	{
		arr = new int[3][3];
	}
	
	public State(State state)
	{
		arr = new int[3][3];
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
				arr[i][j] = state.arr[i][j];
		}
	}
	
	public int mismatch()
	{
		int cnt=0;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(this.arr[i][j]!=goal.arr[i][j])
					cnt++;
			}
		}
		return cnt;
	}
	
	public int manhattan() {
		int cnt=0;
		int i1,j1,i2,j2;
		for(i1=0;i1<3;i1++)
		{
			for(j1=0;j1<3;j1++)
			{
				cnt += computeMan(arr[i1][j1],i1,j1);
			}
		}
		return cnt;
	}
	public int computeMan(int x, int i1, int j1) {
		int i,j=0,cnt=0;
		boolean match =false;
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(goal.arr[i][j]==x)
				{
					match = true;
					break;
				}	
			}
			if(match)
			  break;
		}
		cnt = Math.abs(i-i1)+Math.abs(j-j1);
		return cnt;
	}
	
	public State getUp()
	{
		State nstate = new State(this);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(arr[i][j]==9)
				{
					try
					{
						nstate.level = this.level+1;
						nstate.parent = this;
						nstate.arr[i][j] = this.arr[i-1][j];
						nstate.arr[i-1][j] = 9;
						System.out.println("Level"+this.level);
						return nstate;
					}
					catch(Exception e)
					{
						continue;
					}
				}
			}
		}
		return null;
	}
	
	public State getDown()
	{
		State nstate = new State(this);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(arr[i][j]==9)
				{
					try
					{
						nstate.level = this.level+1;
						nstate.parent = this;
						nstate.arr[i][j] = this.arr[i+1][j];
						nstate.arr[i+1][j] = 9;
						System.out.println("Leveld"+this.level);
						return nstate;
						
					}
					catch(Exception e)
					{
						continue;
					}
				}
			}
		}
		return null;
	}
	
	public State getRight()
	{
		State nstate = new State(this);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(arr[i][j]==9)
				{
					try
					{
						nstate.level = this.level+1;
						nstate.parent = this;
						nstate.arr[i][j] = this.arr[i][j+1];
						nstate.arr[i][j+1] = 9;
						System.out.println("LevelR"+this.level);
						return nstate;
					}
					catch(Exception e)
					{
						continue;
					}
				}
			}
		}
		return null;
	}
	
	public State getLeft()
	{
		State nstate = new State(this);
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(arr[i][j]==9)
				{
					try
					{
						nstate.level = this.level+1;
						nstate.parent = this;
						nstate.arr[i][j] = this.arr[i][j-1];
						nstate.arr[i][j-1] = 9;
						System.out.println("LevelL"+this.level);
						return nstate;
					}
					catch(Exception e)
					{
						continue;
					}
				}
			}
		}
		return null;
	}
	
	@Override
	public boolean equals(Object obj) {
		// TODO Auto-generated method stub
		State s = (State)obj;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(this.arr[i][j]!=s.arr[i][j])
					return false;
			}
		}
		return true;
	}

	@Override
	public String toString() {
		int i,j;
		String s="";
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				if(arr[i][j]!=9)
					s=s+arr[i][j]+"\t";
				else
					s=s+" \t";
			}
			s=s+"\n";
		}
		return s;
	}

	@Override
	public int compareTo(State obj) {
		// TODO Auto-generated method stub
		int u = this.level + this.mismatch();
		int v = obj.level + obj.mismatch();
		if(u>v)
			return 1;
		else if(u<v) 
			return -1;
		
		int x = this.manhattan() + this.level;
		int y = obj.manhattan() + obj.level;
		if(x>y)
			return 1;
		else if(x<y) 
			return -1;
		
		return 0;
	}
	
}
