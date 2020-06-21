/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Calculadora;
import java.rmi.Remote;
import java.rmi.RemoteException;
/**
 *
 * @author Alexis
 */
public interface Calculadora extends Remote{
    int suma(int x,int y) throws RemoteException;
    int resta(int x,int y) throws RemoteException;
    int mult(int x,int y) throws RemoteException;
    double division(double a,double b) throws RemoteException;
}
