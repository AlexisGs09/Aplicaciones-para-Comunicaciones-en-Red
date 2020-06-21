/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package calculadorarmi;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import Calculadora.*;
/**
 *
 * @author Alexis
 */
public class Cliente {
    private Cliente() {}

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        String host = (args.length < 1) ? null : args[0];
	try {
	    Registry registry = LocateRegistry.getRegistry(host);	
            //también puedes usar getRegistry(String host, int port)
            Calculadora stub = (Calculadora) registry.lookup("Calculadora");
            int x=5,y=4;
	    double a=5,b=4;
	    int response = stub.suma(x,y);
            int respRest = stub.resta(x,y);
            int respMult = stub.mult(x,y);
            double respDiv = stub.division(a,b);
	    System.out.println("Calculadora RMI");
	    System.out.println("Respuesta suma: "+x+" + "+y+" = " + response);
            System.out.println("Respuesta resta: "+x+" - "+y+" = " + respRest);
            System.out.println("Respuesta multiplicacion: "+x+" * "+y+" = " + respMult);
            System.out.println("Respuesta division: "+x+" / "+y+" = " + respDiv);
	} catch (Exception e) {
	    System.err.println("Excepción del cliente: " + e.toString());
	}
    }
}