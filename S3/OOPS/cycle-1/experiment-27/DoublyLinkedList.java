/*
 * Experiment - 27
 * Doubly Linked List in java using collections framework
 * Athul Anoop
 * 07-10-24
 */

import java.util.LinkedList;
import java.util.*;

public class DoublyLinkedList {
	public static void main(String[] args){
		LinkedList<Integer> list = new LinkedList<Integer>();
		list.add(10);
		list.add(-50);
		list.add(91);
		System.out.println("Doubly Linked List: "+list);
		list.remove(new Integer(-50));
		System.out.println("Doubly Linked List: "+list);
	}
}
