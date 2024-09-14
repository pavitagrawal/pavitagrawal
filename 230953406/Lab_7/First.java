class First {
    private String name;
    private int id;
    private String college_name;

    public First(String name, int id, String college_name) {
        this.name = name;
        this.id = id;
        this.college_name = college_name;
    }

    public void display_details() {
        System.out.println("Name: " + name);
        System.out.println("ID: " + id);
        System.out.println("College Name: " + college_name);
    }

    public static void main(String[] args) {
        First student1 = new First("John Doe", 101, "MIT");
        student1.display_details();
    }
}
