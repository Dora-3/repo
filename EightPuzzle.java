import java.util.*;
public class EightPuzzle {
   static Scanner sc = new Scanner(System.in);
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Queue<State> q = new PriorityQueue<>();
		List<State> L = new ArrayList<>();
		State temp=null,curr,next = null;
		curr = new State();
		System.out.println("Enter initial State (use 9 for blank): ");
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
				curr.arr[i][j]=sc.nextInt();
		}
		curr.level = 0;
		State.goal = new State();
		State.goal.arr = new int[3][3];
		System.out.println("Enter final State (use 9 for blank): ");
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
				State.goal.arr[i][j]=sc.nextInt();
		}
		q.offer(curr);
		System.out.println("Hi"+q);
		while(true)
		{
			curr = q.poll();
			System.out.println("noway"+curr);
			if(L.contains(curr))
				continue;
			else
				L.add(curr);
			if(curr==null)
				break;
			if(curr.equals(State.goal))
				break;
			
			next = curr.getUp();
			System.out.println("Hello"+next);
			if(next!=null)
			{
				if(!q.contains(next))
				{
					System.out.println("Bye"+q.contains(next));
					q.offer(next);
					System.out.println("Bye333"+q.offer(next));
					
				}
				else
				{
					for(State st : q)
					{
						if(next.equals(st) && next.compareTo(st)<0)
							temp=st;
					}
					if(temp!=null)
					{
						q.remove(temp);
						q.offer(next);
						temp=null;
					}
				}
			}
			
			next = curr.getDown();
			if(next!=null)
			{
				if(!q.contains(next))
				{
					q.offer(next);
				}
				else
				{
					for(State st : q)
					{
						if(next.equals(st) && next.compareTo(st)<0)
							temp=st;
					}
					if(temp!=null)
					{
						q.remove(temp);
						q.offer(next);
						temp=null;
					}
				}
			}
			
			next = curr.getLeft();
			if(next!=null)
			{
				if(!q.contains(next))
				{
					q.offer(next);
				}
				else
				{
					for(State st : q)
					{
						if(next.equals(st) && next.compareTo(st)<0)
							temp=st;
					}
					if(temp!=null)
					{
						q.remove(temp);
						q.offer(next);
						temp=null;
					}
				}
			}
			
			next = curr.getRight();
			if(next!=null)
			{
				if(!q.contains(next))
				{
					q.offer(next);
				}
				else
				{
					for(State st : q)
					{
						if(next.equals(st) && next.compareTo(st)<0)
	;						temp=st;
					}
					if(temp!=null)
					{
						q.remove(temp);
						q.offer(next);
						temp=null;
					}
				}
			}
		}
		for(State st:L)
			System.out.println(st);
	}

}
