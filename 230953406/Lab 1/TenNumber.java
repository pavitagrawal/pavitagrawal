import java.util.Scanner;
class TenNumber
{
	public static void main(String args[])
	{
		int positive = 0, negative = 0, zeros = 0;
		int a[] = new int[10];
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the 10 numbers");
		for(int i=0;i<10;i++){
			a[i] = sc.nextInt();
		}
		for(int i=0;i<10;i++){
			if(a[i]==0){
				zeros++;
			}
			else if(a[i]>0){
				positive++;
			}
			else{
				negative++;
			}
		}
		System.out.println("No. of positive: "+positive);
		System.out.println("No. of negative: "+negative);
		System.out.println("No. of zeroes: "+zeros);
	}
}
