public class Vertex {
    public static double eps = 1e-6;

    public static double dist(Vertex a, Vertex b) {
        return Math.sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }

    public double x, y;
    public int ind;

    public Vertex(double X, double Y, int Ind) {
        this.x = X;
        this.y = Y;
        this.ind = Ind;
    }
}
