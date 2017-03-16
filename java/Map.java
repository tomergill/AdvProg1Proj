import javafx.scene.image.Image;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Class representing the map and the things on it.
 */
public class Map {
    private int width, height;
    private List<Point> obstacles;
    private List<Taxi> cabs;
    private List<Driver> drivers;
    private AtomicBoolean hasChanged;

    private static final Image roadImg = new Image("./resources/road.jpg"),
            obstacleImg = new Image("./resources/roadblock.png");

    /**
     * Ctor, Width/Height bigger than 10 / smaller than 0 are rounded to 10 / 0 accordingly.
     * @param width width of map, between 1 to 10.
     * @param height height of map, between 1 to 10.
     */
    public Map(int width, int height) {
        if (height > 10)
            this.height = 10;
        else if (height < 0)
            this.height = 1;
        else
            this.height = height;

        if (width > 10)
            this.width = 10;
        else if (width < 0)
            this.width = 0;
        else
            this.width = width;

        this.obstacles = new ArrayList<>();
        this.cabs = new ArrayList<>();
        this.drivers = new ArrayList<>();
        this.hasChanged = new AtomicBoolean(true);
    }

    /**
     * @return the width of the map.
     */
    public int getWidth() {
        return width;
    }

    /**
     * @return the height of the map.
     */
    public int getHeight() {
        return height;
    }

    /**
     * @return the image of a road.
     */
    public static Image getRoadImg() {
        return roadImg;
    }

    /**
     * @return the image of an obstacle.
     */
    public static Image getObstacleImg() {
        return obstacleImg;
    }

    /**
     * Adds a Taxi to the map.
     * @param t Taxi to add.
     */
    public void addTaxi(Taxi t) {
        try {
            cabs.add((Taxi) t.clone());
        } catch (CloneNotSupportedException e) {
            cabs.add(t);
        }
        this.hasChanged.set(true);
    }

    /**
     * Adds obstacle.
     * @param p location of obstacle.
     */
    public void addObstacle(Point p) {
        int x = p.getX(), y = p.getY();
        if (x >= 0 && y >= 0 && x < width && y < height) {
            obstacles.add(p);
            this.hasChanged.set(true);;
        }
    }

    /**
     * Adds obstacle.
     * @param x x-value of the obstacle.
     * @param y y-value of the obstacle.
     */
    public void addObstacle(int x, int y) {
        addObstacle(new Point(x,y));
    }

    /**
     * Gets the image of the requested tile.
     * @param x x-value of tile's location.
     * @param y y-value of tile's location.
     * @return The image of the tile, or null if requested tile isn't in the map.
     */
    public Image getImageOfTile(int x, int y) {
        if (x < 0 || y < 0 || x >= width || y >= height)
            return null;
        for (Point p: obstacles) {
            if (p.isEqual(x,y))
                return obstacleImg;
        }
        for (Taxi t:cabs) {
            if (t.getLocation().isEqual(x,y))
                return t.getImage();
        }
        return roadImg;
    }

    /**
     * @param id id of the requested taxi.
     * @return the requested taxi, or null if there isn't one.
     */
    private Taxi getTaxiById(int id) {
        for (Taxi t: cabs) {
            if (t.isEqual(id))
                return t;
        }
        return null;
    }

    /**
     * Sets the location of the driver.
     * @param id id of the driver.
     * @param location new location.
     */
    public void setDriverLocation(int id, Point location) {
        Taxi t = getTaxiByDriverId(id);
        if (t != null) {
            t.setLocation(location);
            this.hasChanged.set(true);
        }
    }

    /**
     * Sets the location of the taxi.
     * @param id id of the taxi.
     * @param location new location.
     */
    public void setTaxiLocation(int id, Point location) {
        Taxi t = getTaxiById(id);
        if (t != null) {
            t.setLocation(location);
            this.hasChanged.set(true);
        }
    }

    /**
     * @param id id of the taxi.
     * @return the location of the requested taxi.
     */
    public Point getTaxiLocation(int id) {
        Taxi t = getTaxiById(id);
        if (t != null)
            return t.getLocation();
        return null;
    }

    /**
     * @param id the requested driver's id.
     * @return the requested driver or null if there isn't one.
     */
    private Driver getDriverById(int id) {
        for (Driver d:drivers) {
            if (d.isEqual(id))
                return d;
        }
        return null;
    }

    /**
     * @param id of the driver.
     * @return The taxi of the requested driver, or null if teh driver doesn't exist or it has no
     * cab.
     */
    private Taxi getTaxiByDriverId(int id) {
        Driver d = getDriverById(id);
        if (d == null)
            return null;
        if (d.getCabId() == -1)
            return null;
        return getTaxiById(d.getCabId());
    }

    /**
     * @param id of the requested driver.
     * @return the location of the driver, or null if he doesn't exist or has no taxi.
     */
    public Point getDriverLocation(int id) {
        Taxi t = getTaxiByDriverId(id);
        if (t == null)
            return null;
        return t.getLocation();
    }

    /**
     * @return true if the map has changed since the last time checked. Otherwise false.
     */
    public boolean hasChanged() {
        return hasChanged.get();
    }

    /**
     * Indicates that the map has been checked now.
     */
    public synchronized void check() {
        this.hasChanged.set(false);
    }

    /**
     * Adds the driver
     * @param d the driver
     */
    public void addDriver(Driver d) {
        drivers.add(d);
        hasChanged.set(true);
    }

    /**
     * Creates a map from the input of the server.
     * @param input input from server.
     * @return created map.
     */
    public static Map createMapFromInput(String input) {
        String[] arr = input.split(" ");
        Map map = new Map(Integer.parseInt(arr[0]), Integer.parseInt(arr[1]));
        if (arr.length > 2) {
            for (int i = 2; i < arr.length; i++) {
                map.addObstacle(Integer.parseInt(arr[i].substring(0,1)),
                        Integer.parseInt(arr[i].substring(2)));
            }
        }
        return map;
    }
}
