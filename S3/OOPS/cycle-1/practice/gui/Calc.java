
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class Build implements ActionListener {
    JFrame window;
    JPanel panels[] = new JPanel[3];
    JLabel exp;
    JTextField result;
    String operators[] = {"+", "-", "*", "=","/"};
    Double operands[] = new Double[2];
    String operator;

    Build (){
        window = new JFrame("Calc");
        window.setBounds(300, 300, 300, 500);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        window.setLayout(new GridLayout(3,1));

        exp = new JLabel();
        result = new JTextField("");
        result.setEditable(false);

        for (int i = 0; i < 3; i++){
            JPanel panel = new JPanel();
            panels[i] = panel;
            window.add(panel);
        }

        panels[0].setLayout(new GridLayout(1,1));
        panels[0].add(result);

        panels[1].setLayout(new GridLayout(1,1));
        panels[1].add(exp);

        panels[2].setLayout(new GridLayout(4,4));

        int tmp = 0;
        for (int i = 1; i < 17; i++){
            JButton btn;
            if (i%4 == 0 ){
                btn = new JButton(operators[tmp]);
                tmp++;
            } else if (i == 13){
                btn = new JButton(operators[4]);
            } else if (i == 14){
                btn = new JButton("0");
            } else if (i == 15){
                btn = new JButton("DEL");
            } else {
                btn = new JButton(""+(i-tmp));
            }
            btn.addActionListener(this);
            panels[2].add(btn);
        }
        window.setVisible(true);
    }
    public void actionPerformed(ActionEvent e){
        String s = e.getActionCommand();
        if (Character.isDigit(s.charAt(0))){
            result.setText(result.getText()+s);
        } else if (s.equals("DEL")){
            result.setText("");
        } else if (s.equals("=")){
            operands[1] = Double.parseDouble(result.getText());
            exp.setText(exp.getText()+operands[1]);
            Double output = 0.0;
            switch (operator){
                case "+":
                    output = operands[0]+operands[1];
                    break;
                case "-":
                    output = operands[0]-operands[1];
                    break;
                case "*":
                    output = operands[0]*operands[1];
                    break;
                case "/":
                    try{
                        if (operands[1] == 0.0){
                            throw new ArithmeticException();
                        }
                        output = operands[0]/operands[1];
                    }
                    catch(ArithmeticException ae){
                        JOptionPane.showMessageDialog(window, "Divisor cannot be ZERO!");
                    }
                    break;
                default:
                    break;
            }
            result.setText(output+"");

        } else {
            operands[0] = Double.parseDouble(result.getText());
            operator = s;
            exp.setText(operands[0]+""+s);
            result.setText("");
        }
    }
}
public class Calc {
    public static void main(String[] args){
        Build build = new Build();
    }
}

