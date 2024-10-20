import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Build extends JFrame implements ActionListener {
    JFrame window;
    JPanel red, yellow, green, buttons, lights;
    JRadioButton rBtn, yBtn, gBtn;
    ButtonGroup bg = new ButtonGroup();

    Build() {
        window = new JFrame();
        window.setSize(200, 600);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLayout(new GridLayout(2, 1));
        
        red = new JPanel();
        red.setSize(200, 100);
        yellow = new JPanel();
        yellow.setSize(200, 100);
        green = new JPanel();
        green.setSize(200, 100);
        lights = new JPanel();
        lights.setLayout(new GridLayout(3, 1));
        lights.add(red);
        lights.add(yellow);
        lights.add(green);
        
        buttons = new JPanel();
        buttons.setSize(100, 100);
        rBtn = new JRadioButton("Red");
        yBtn = new JRadioButton("Yellow");
        gBtn = new JRadioButton("Green");
        bg.add(rBtn);
        bg.add(yBtn);
        bg.add(gBtn);
        buttons.add(rBtn);
        buttons.add(yBtn);
        buttons.add(gBtn);
        rBtn.addActionListener(this);
        yBtn.addActionListener(this);
        gBtn.addActionListener(this);
        window.add(lights);
        window.add(buttons);
        window.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        String s = e.getActionCommand();
        red.setBackground(null);
        green.setBackground(null);
        yellow.setBackground(null);
        System.out.println(s);
        if (s.equals("Red")) {
            red.setBackground(Color.red);
        }
        if (s.equals("Yellow")) {
            yellow.setBackground(Color.yellow);
        }
        if (s.equals("Green")) {
            green.setBackground(Color.green);
        }
    }
}

public class TrafficLights {
    public static void main(String[] args) {
        Build traffic = new Build();
    }
}
