/**
 * Class representing a taxi driver.
 */
public class Driver {
    private int id;
    private int cabId;

    /**
     * Ctor, initializes the driver without a cab.
     * @param id id of the driver.
     */
    public Driver(int id) {
        this.id = id;
        this.cabId = -1;
    }

    /**
     * Ctor.
     * @param id id of the driver.
     * @param cabId id of the driver's cab.
     */
    public Driver(int id, int cabId) {
        this(id);
        this.cabId = cabId;
    }

    /**
     * @return the driver's id.
     */
    public int getId() {
        return id;
    }

    /**
     * @return the driver's cab's id.
     */
    public int getCabId() {
        return cabId;
    }

    /**
     * Assigns a cab to this driver.
     * @param cabId new cab's id.
     */
    public void assignCabToDriver(int cabId) {
        this.cabId = cabId;
    }

    /**
     * @return True if the driver has a cab, otherwise false.
     */
    public boolean hasTaxi() {
        return cabId >= 0;
    }

    /**
     * @param id id of the other driver to compare.
     * @return true if drivers are equal, otherwise false.
     */
    public boolean isEqual(int id) {
        return id == this.id;
    }

    /**
     * @param other other driver to compare.
     * @return true if drivers are equal, otherwise false.
     */
    public boolean isEqual(Driver other) {
        return isEqual(other.getId());
    }
}
