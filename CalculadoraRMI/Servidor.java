/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package calculadorarmi;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import Calculadora.*;
import java.rmi.AlreadyBoundException;
/**
 *
 * @author Alexis
 */
public class Servidor implements Calculadora{
    public Servidor() {}

    public int suma(int x, int y) {
        System.out.println("Corriendo en el servidor");
	return x+y;
    }
    public int resta(int x, int y){
        System.out.println("Corriendo en el servidor");
        return x-y;
    }
    public int mult(int x, int y){
        System.out.println("Corriendo en el servidor");
        return x*y;
    }
    public double division(double a, double b){
        System.out.println("Corriendo en el servidor");
        return a/b;
    }

        public static void main(String args[]) {
	try {
               //puerto default del rmiregistry
               java.rmi.registry.LocateRegistry.createRegistry(1099); 
               System.out.println("RMI registro listo.");
	} catch (RemoteException e) {
               System.out.println("Excepcion RMI del registry:");
           }//catch

           try {
                System.setProperty("java.rmi.server.codebase", "file:/c:/Temp/Calculadora/");
	    Servidor obj = new Servidor();
	    Calculadora stub = (Calculadora) UnicastRemoteObject.exportObject(obj, 0);
        
	    // Ligamos el objeto remoto en el registro
	    Registry registry = LocateRegistry.getRegistry();
	    registry.bind("Calculadora", stub);
          
	    System.err.println("Servidor listo...");
	} catch (AlreadyBoundException | RemoteException e) {
	    System.err.println("Excepción del servidor: " + e.toString());
	}
      }

 
   
    
        

}
