package iot.unipi.it;

import java.sql.*;

public class DbUtility {

	 @SuppressWarnings("finally")
		private static Connection makeJDBCConnection() {
		Connection databaseConnection = null;

        String databaseIP = "localhost";
        String databasePort = "3306";
        String databaseUsername = "root";
        String databasePassword = "PASSWORD";
        String databaseName = "db_sluiceGate";
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
            return databaseConnection;
        }

        try {
            databaseConnection = DriverManager.getConnection(
                    "jdbc:mysql://" + databaseIP + ":" + databasePort +
                            "/" + databaseName + "?zeroDateTimeBehavior=CONVERT_TO_NULL&serverTimezone=CET",
                    databaseUsername,
                    databasePassword);
            if (databaseConnection == null) {
                System.err.println("Connection to DB failed");
            }
        } catch (SQLException e) {
        	System.err.println("MySQL connection Failed!\n");
            e.printStackTrace();
        }finally {
            return databaseConnection;
        }
    }
	 
	public static void insertLevel(final double level) {
    	String insertQueryStatement = "INSERT INTO water_level_landside (timestamp, water_level) VALUES (CURRENT_TIMESTAMP, ?)";
    	try (Connection smartPoolConnection = makeJDBCConnection();
        		PreparedStatement smartPoolPrepareStat = smartPoolConnection.prepareStatement(insertQueryStatement);
           ) {
    		smartPoolPrepareStat.setDouble(1, level);        	                
        	smartPoolPrepareStat.executeUpdate();
 
    	 } catch (SQLException sqlex) {
             sqlex.printStackTrace();
         }
	}

    public static void insertSalinity(final double salinity) {
    	String insertQueryStatement = "INSERT INTO salinity (timestamp, salinity) VALUES (CURRENT_TIMESTAMP, ?)";
    	try (Connection smartPoolConnection = makeJDBCConnection();
        		PreparedStatement smartPoolPrepareStat = smartPoolConnection.prepareStatement(insertQueryStatement);
           ) {
    		smartPoolPrepareStat.setDouble(1, salinity);        	                
        	smartPoolPrepareStat.executeUpdate();
 
    	 } catch (SQLException sqlex) {
             sqlex.printStackTrace();
         }
	}
}
