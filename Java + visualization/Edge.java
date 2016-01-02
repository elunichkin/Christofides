public class Edge implements Comparable<Edge> {
    public Vertex u, v;
    public double dist;

    public Edge(Vertex U, Vertex V) {
        this.u = U;
        this.v = V;
        dist = Vertex.dist(u, v);
    }

    @Override
    public int compareTo(Edge other) {
        if (Math.abs(this.dist - other.dist) < Vertex.eps)
            return 0;
        return (int)Math.signum(this.dist - other.dist);
    }
}
