
import java.util.*;

class Warehouse {
    String productId;
    int quantity;
    int unitCost;

    public Warehouse(String productId, int quantity, int unitCost) {
        this.productId = productId;
        this.quantity = quantity;
        this.unitCost = unitCost;
    }
}

class Order {
    int orderedQuantity;
    int orderID;
    String date;

    public Order(int orderedQuantity, int orderID, String date) {
        this.orderedQuantity = orderedQuantity;
        this.orderID = orderID;
        this.date = date;
    }
}

class OrderException extends Exception {
    public OrderException(String message) {
        super(message);
    }
}

class BookOrderThread extends Thread {
    private Warehouse warehouse;
    private Order order;

    public BookOrderThread(Warehouse warehouse, Order order) {
        this.warehouse = warehouse;
        this.order = order;
    }

    public void run() {
        try {
            checkAvailableQuantity();
            computeTotCost();
        } catch (OrderException e) {
            System.out.println(e.getMessage());
        }
    }

    private synchronized void checkAvailableQuantity() throws OrderException {
        if (warehouse.quantity == 0) {
            throw new OrderException("Order cannot be placed");
        }
        if (order.orderedQuantity <= 0) {
            throw new OrderException("Order quantity is invalid");
        }
        if (order.orderedQuantity > warehouse.quantity) {
            throw new OrderException("Out of Stock for " + warehouse.productId);
        }
        warehouse.quantity -= order.orderedQuantity;
    }

    private void computeTotCost() {
        int totalCost = order.orderedQuantity * warehouse.unitCost;
        System.out.println("Order ID: " + order.orderID + ", Total Cost: " + totalCost);
    }
}

public class OrderManagement {
    private static Map<String, Warehouse> warehouseMap = new HashMap<>();
    private static List<Order> orderList = new ArrayList<>();

    public static void main(String[] args) {
        warehouseMap.put("P001", new Warehouse("P001", 10, 100));
        warehouseMap.put("P002", new Warehouse("P002", 0, 150));

        placeOrder("P001", 5, 1, "2023-10-01");
        placeOrder("P001", 3, 2, "2023-10-02");
        placeOrder("P002", 1, 3, "2023-10-03");
        placeOrder("P001", 0, 4, "2023-10-04");
        placeOrder("P001", 6, 5, "2023-10-05");
        placeOrder("P003", 2, 6, "2023-10-06");

        displaySortedOrders();
    }

    private static void placeOrder(String productId, int orderedQuantity, int orderID, String date) {
        Warehouse warehouse = warehouseMap.get(productId);
        if (warehouse == null) {
            System.out.println("ProductID does not exist");
            return;
        }
        Order order = new Order(orderedQuantity, orderID, date);
        BookOrderThread orderThread = new BookOrderThread(warehouse, order);
        orderThread.start();
        try {
            orderThread.join();
            orderList.add(order);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private static void displaySortedOrders() {
        Collections.sort(orderList, Comparator.comparing(o -> o.date));
        System.out.println("Sorted Order Details:");
        for (Order order : orderList) {
            System.out.println("Order ID: " + order.orderID + ", Date: " + order.date + ", Quantity: " + order.orderedQuantity);
        }
    }
}
