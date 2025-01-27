import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class buildCalculator implements ActionListener {
    JFrame window;
    JPanel buttonPanel, resultPanel;
    JButton[] button = new JButton[10];
    JLabel exp;
    JTextField result;
    Double op1, op2;
    String op, number;
    String[] operators = {"+", "-", "*", "=", "/"};

    buildCalculator() {
        window = new JFrame("Calculator");
        window.setBounds(300, 500, 300, 500);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLayout(new GridLayout(2, 1));

        buttonPanel = new JPanel();
        resultPanel = new JPanel();
        exp = new JLabel();
        result = new JTextField("");
        result.setEditable(false);
        int tmp = 0;

        for (int i = 1; i < 17; i++) {
            JButton btn;
            if (i%4 == 0) {
                btn = new JButton(operators[i/4-1]);
                tmp++;
            } else if ( i>12 && i<16) {
                switch (i) {
                    case 13:
                        btn = new JButton(operators[4]);
                        break;
                    case 14:
                        btn = new JButton("0");
                        break;
                    default:
                        btn = new JButton("DEL");
                        break;
                }
            } else {
                btn = new JButton("" + (i-tmp));
            }
            btn.addActionListener(this);
            buttonPanel.add(btn);
        }

        buttonPanel.setLayout(new GridLayout(4, 4));
        resultPanel.add(result);
        resultPanel.add(exp);
        resultPanel.setLayout(new GridLayout(2, 1));

        window.add(resultPanel);
        window.add(buttonPanel);
        window.setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        String s = e.getActionCommand();
        if (Character.isDigit(s.charAt(0))) {
            number = result.getText() + s;
            result.setText(number);
        }
        else if (!s.equals("=") && !s.equals("DEL")) {
                op1 = Double.parseDouble(result.getText());
                op = s;
                exp.setText(op1 + op);
                result.setText("");
        } else if (s.equals("=")) {
            op2 = Double.parseDouble(result.getText());
            exp.setText(exp.getText() + "" + op2);
            switch (op) {
                case "+":
                    result.setText("" + (op1 + op2));
                    break;
                case "-":
                    result.setText("" + (op1 - op2));
                    break;
                case "*":
                    result.setText("" + (op1 * op2));
                    break;
                case "/":
                    try {
                        if (op2 == 0)
                            throw new ArithmeticException();
                        result.setText("" + (op1 / op2));
                        break;
                    } catch (ArithmeticException ae) {
                        JOptionPane.showMessageDialog(window, "Divisor can not be ZERO");
                    }
            }
        } else if (s.equals("DEL")) {
            result.setText("");
        }
    }
}

public class SimpleCalculator {
    public static void main(String[] args) {
        buildCalculator calc = new buildCalculator();
    }
}
