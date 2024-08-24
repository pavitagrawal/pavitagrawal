import java.util.Scanner;
class Leap{
	public static void main(String args[]){
		int year;
		boolean a;
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter the year: ");
		year = sc.nextInt();
		if(year%4!=0){
			a = false;
		}
		else if(year%100!=0){
			a = true;
		}
		else if(year%400!=0){
			a = false;
		}
		else{
			a = true;
		}
		if(a == true){
			System.out.println("It is a leap year");
		}
		else{
			System.out.println("It is not a leap year");
		}
	}
}