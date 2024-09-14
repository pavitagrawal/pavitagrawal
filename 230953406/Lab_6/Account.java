import java.util.Scanner;

class Account {
    private String custName;
    private int accNo;
    private String accType;
    private double bal;
    private static final Scanner in = new Scanner(System.in);

    public void enterDetails() {
        System.out.print("Enter name of customer: ");
        custName = in.nextLine();
        System.out.print("Enter account number: ");
        accNo = in.nextInt();
        System.out.print("Enter balance: ");
        bal = in.nextDouble();
        in.nextLine(); // Consume newline left-over
    }

    public void printDetails() {
        System.out.println("Name of customer: " + custName);
        System.out.println("Account number: " + accNo);
        System.out.println("Account type: " + accType);
        System.out.println("Balance: " + bal);
    }

    public void printBalance() {
        System.out.println("Account number: " + accNo);
        System.out.println("Balance: " + bal);
    }

    protected void setAccType(String accType) {
        this.accType = accType;
    }

    protected double getBalance() {
        return bal;
    }

    protected void updateBalance(double amount) {
        this.bal += amount;
    }

    protected boolean canWithdraw(double amount) {
        return (bal - amount >= 10000.0);
    }
}

class CurrentAccount extends Account {
    public CurrentAccount() {
        setAccType("Current");
        enterDetails();
        printDetails();
    }

    public void deposit() {
        System.out.print("Enter amount to deposit: ");
        double dep = sc.nextDouble();
        updateBalance(dep);
        printBalance();
    }

    public void withdraw() {
        System.out.print("Enter amount to withdraw: ");
        double with = sc.nextDouble();
        if (!canWithdraw(with)) {
            System.out.println("Insufficient funds");
        } else {
            updateBalance(-with);
            printBalance();
        }
    }

    public void minCheck() {
        double penalty = 0.02;
        if (getBalance() < 10000) {
            System.out.println("Balance lower than minimum");
            updateBalance(-penalty * getBalance());
            printBalance();
        }
    }
}

class Savings extends Account {
    public Savings() {
        setAccType("Savings");
        enterDetails();
        printDetails();
    }

    public void withdraw() {
        System.out.print("Enter amount to withdraw: ");
        double with = sc.nextDouble();
        if (!canWithdraw(with)) {
            System.out.println("Insufficient funds");
        } else {
            updateBalance(-with);
            printBalance();
        }
    }

    public void interest() {
        int rate = 5;
        System.out.print("Enter time for interest: ");
        double time = sc.nextDouble();
        double si = (getBalance() * rate * time) / 100;
        System.out.println("Interest to be deposited: " + si);
        updateBalance(si);
        printBalance();
    }
}

class AccountMain {
    public static void main(String[] args) {
        CurrentAccount curAcc = new CurrentAccount();
        Savings savAcc = new Savings();
        curAcc.deposit();
        curAcc.minCheck();
        curAcc.withdraw();
        savAcc.withdraw();
        savAcc.interest();
    }
}