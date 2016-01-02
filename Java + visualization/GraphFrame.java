import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class GraphFrame extends JFrame {
    private GraphPanel graphPanel;

    public GraphFrame(int mc) {
        super("Christofides visualization");
        JPanel cp = new JPanel(new BorderLayout());
        cp.setBorder(BorderFactory.createCompoundBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5),
                BorderFactory.createLineBorder(Color.black)));
        setContentPane(cp);
        graphPanel = new GraphPanel(mc);
        cp.add(graphPanel, BorderLayout.CENTER);
        setSize(700, 700);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }

    public GraphPanel getGraphPanel() {
        return graphPanel;
    }
}
