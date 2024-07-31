import java.util.Arrays;
import java.util.Scanner;

class Matrix {
	private int rows;
	private int columns;
	public int[][] data;

	Matrix(int rows, int columns){
		this.rows = rows;
		this.columns = columns;
		this.data = new int[rows][columns];
	};

	public void readElements(){
		Scanner scanner = new Scanner(System.in);
		System.out.println("Matrix Elements: ");
		for (int i = 0; i < this.rows;i++){
			String elements[] = scanner.nextLine().split(",");
			for (int j = 0; j< this.columns; j++){
				this.data[i][j] = Integer.parseInt(elements[j]);
			}
		}
	}

	public void display(){
		System.out.print("[ ");
		for (int i=0; i<rows;i++){
			System.out.print("[ ");
			for (int j = 0; j< columns; j++){
				System.out.printf("%d, ", this.data[i][j]);
			}
			System.out.print("], \n");
		}
		System.out.print("]\n");
	}


	public Matrix multiply(Matrix other){
		if (this.columns != other.rows) throw new Error("Operand dimensions do not satisfy requirements for multiplication");
		Matrix result = new Matrix(this.rows, other.columns);
		for (int i=0; i<rows;i++){
			for (int j = 0; j< columns; j++){
				for (int k = 0; k < this.columns; k++){
					result.data[i][j] += this.data[i][k]*other.data[k][j];
				}
			}
		}
		return result;
	}

};

public class MatrixMultiplication {

	public static int[] readShape(){
		Scanner scanner = new Scanner(System.in);
		System.out.print("Matrix shape (rows,columns): ");
		String input[] = scanner.nextLine().split(",");
		int rows = Integer.parseInt(input[0]);
		int columns= Integer.parseInt(input[1]);
		int shape[] = {rows, columns};
		return shape;
	}


	public static void main(String args[]){
		int shape[] = readShape();
		Matrix matrixA = new Matrix(shape[0], shape[1]);
		matrixA.readElements();
		matrixA.display();
	}
} 
