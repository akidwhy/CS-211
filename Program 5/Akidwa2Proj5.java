/**
 * This file contains the User Interface code for the Infix Evaluation 
 * Project, Project 5 for CS 211 for Fall 2016.
 * 
 * Date: 3/10/16
 * 
 * @Author - Pat Troy, UIC, CS Department
 * 
 * Abdullah Kidwai
 * akidwa2
 */
import java.io.*;
import java.util.*;

/* recall the name of the public class in the file MUST match the filename
 * (without the file extension)                                            */
public class Akidwa2Proj5
{
  static int debugMode = 0;
  
  public static void main (String[] args)
  {
    if(args.length > 0 && args[0].equals("-d")){
      debugMode = 1;
    }
    Token inputToken;
    TokenReader tr = new TokenReader();
    
    System.out.print ("Starting Expression Evaluation Program\n\n");
    System.out.print ("Enter Expression: ");
    

    inputToken = tr.getNextToken ();
    
    while (inputToken.equalsType(TokenType.QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(TokenType.HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(TokenType.ERROR))
      {
       System.out.print ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(TokenType.EOLN))
      {
       System.out.print ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else 
      {
       processExpression(inputToken, tr);
      } 

      System.out.print ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  System.out.print ("Quitting Program\n");
  return;
    
  }
  
public static void processExpression (Token inputToken, TokenReader tr)
  {
    /**********************************************/
    /* Declare both stack head pointers here      */
    //First Step
    MyStack valStk = new MyStack();
    MyStack opStk = new MyStack();
    
	//Second Step
    /* Loop until the expression reaches its End */
    while (inputToken.equalsType(TokenType.EOLN) == false)
 {
      /* The expression contain a VALUE */
      if (inputToken.equalsType(TokenType.VALUE))
   {
        /* make this a debugMode statement */
        if(debugMode == 1){  
          System.out.print ("Val: " + inputToken.getValue() + ", "); 
        }
        valStk.push(inputToken);
      }
      
      /* The expression contains an OPERATOR */
      if(inputToken.equalsType(TokenType.OPERATOR)){
        /* make this a debugMode statement */
        if(debugMode == 1){
          System.out.print ("OP: " + inputToken.getOperator() + ", ");
        }

        if(inputToken.getOperator() == '('){
          opStk.push(inputToken);
        }
        
        /* check if the current operator is + or - */
        if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-'){

          while(opStk.isEmpty() != 1 && (opStk.top().getOperator() == '+' || opStk.top().getOperator() == '-' || opStk.top().getOperator() == '*' || opStk.top().getOperator() == '/')){

            Token operator = opStk.top();
            opStk.pop();
            int value2 = valStk.top().getValue();
            valStk.pop();
            int value1 = valStk.top().getValue();
            valStk.pop();
            
            Token value3 = new Token();
            int num = 0;
            if(operator.getOperator() == '+'){
              num = value1 + value2;
            }
            if(operator.getOperator() == '-'){
              num = value1 - value2;
            }  
            if(operator.getOperator() == '*'){
              num = value1 * value2;
            }    
            if(operator.getOperator() == '/'){
                num = value1 / value2;
            }
            value3.setToValue( num );
            valStk.push(value3);
            
          }

          opStk.push(inputToken);
        }
        
        /* check if current operator ir * or / */
        if(inputToken.getOperator() == '*' || inputToken.getOperator() == '/'){

          while(opStk.isEmpty() != 1 && (opStk.top().getOperator() == '*' || opStk.top().getOperator() == '/')){

            Token operator = opStk.top();
            opStk.pop();
            int value2 = valStk.top().getValue();
            valStk.pop();
            int value1 = valStk.top().getValue();
            valStk.pop();
            
            Token value3 = new Token();
            int num = 0;

            if(operator.getOperator() == '+'){
              num = value1 + value2;
            }
            if(operator.getOperator() == '-'){
              num = value1 - value2;
            }  
            if(operator.getOperator() == '*'){
              num = value1 * value2;
            }    
            if(operator.getOperator() == '/'){
                num = value1 / value2;
            }
            value3.setToValue( num );
            valStk.push(value3);
          }
		  
          opStk.push(inputToken);
        }
        
        /* check if current operator is a closing parenthese */
        if(inputToken.getOperator() == ')'){
          //check if opStk is empty
          if(opStk.isEmpty() == 1){
            System.out.println("ERROR - opStk is empty\n");
          }
          else{
            opStk.pop();
          }
        }
      }
      
      inputToken = tr.getNextToken ();
    } 
    
    
    //Third Step
    while(opStk.isEmpty() != 1){
      if(opStk.isEmpty() == 1){
        break;
      }
      Token operator = opStk.top();
      opStk.pop();
      int value1 = valStk.top().getValue();
      valStk.pop();
      int value2 = valStk.top().getValue();
      valStk.pop();
      
      Token value3 = new Token();
      int num = 0;

      if(operator.getOperator() == '+'){
        num = value1 + value2;
      }
      if(operator.getOperator() == '-'){
        num = value1 - value2;
      }  
      if(operator.getOperator() == '*'){
        num = value1 * value2;
      }    
      if(operator.getOperator() == '/'){
          num = value1 / value2;
      }
      value3.setToValue( num );
      valStk.push(value3);
    }
    
      //print out the top of the valStk at the result of the expression
      System.out.println("Top of valStk: " + valStk.top().getValue() + "\n");
	
	if(valStk.isEmpty() == 1){
      System.out.println("ERROR - valStk is empty!!\n");
    }
    valStk.pop();
    System.out.print ("\n");
  }
  
/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/




public static void printCommands()
{
 System.out.print ("The commands for this program are:\n\n");
 System.out.print ("q - to quit the program\n");
 System.out.print ("? - to list the accepted commands\n");
 System.out.print ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

}

class TokenReader
{
  private BufferedReader br;
  private String inline;
  private boolean needline;
  private int pos;
  
  // initialize the TokenReader class to read from Standard Input
  public TokenReader()
  {
    // set to read from Standard Input
    br = new BufferedReader (new InputStreamReader (
        System.in));
    inline = "";
    pos = 0;
    needline = true;
  }
  
  // Force the next getNextToken to read in a line of input
  public void clearToEoln()
  {
    needline = true;
  }
  
  // Return the next Token from the input line
  public Token getNextToken()
  {
    // get a new line of input from user
    if (needline)
    {
      try{
        inline = br.readLine();
      }
      catch (IOException ioe)
      {
        System.out.println ("Error in reading");
        return new Token (TokenType.EOF);
      }
      if (inline == null)
      { // End of File Encoutered - Should never be the case when reading 
        //   from standard input: System.in
        return new Token (TokenType.EOF);
      }
      
      inline = inline + " ";    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }
    
    // skip over any white space characters in the beginning of the input
    while ( pos < inline.length() && 
            Character.isWhitespace(inline.charAt(pos)))
    {
      pos++;
    }
    
    // check for the end of the current line of input
    if (pos >= inline.length())
    {  // at end of line
      needline = true;
      return new Token (TokenType.EOLN);
    }
      
    // Get the next character from the input line
    char ch = inline.charAt(pos); pos++;
    
    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return new Token (TokenType.QUIT);
    }
    
    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return new Token (TokenType.HELP);
    }
    
    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t = new Token();
      t.setToOperator( ch );
      return t;
    }
     
    // check for a number  ==> VALUE Token
    if (Character.isDigit(ch))
    {
      int number = Character.digit(ch, 10);
      ch = inline.charAt(pos); pos++;
      while (Character.isDigit(ch))
      {
        number = number * 10 + Character.digit(ch, 10);
        ch = inline.charAt(pos); pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t = new Token();
      t.setToValue( number );
      return t; 
    }
   
    // Input in not valid if code get to this part ==> ERROR Token
    return new Token (TokenType.ERROR);
  }
    
}
  
// Enumarated Type specifying all of the Tokens
enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOF
}

// Class to hold the Token information
class Token
{
  private TokenType type;
  private char      operator;       // using '$' as undefined/error
  private int       val;      // using -999 as undefined/error
  
  // Default to initialize to the ERROR TokenType
  public Token()
  {
    type = TokenType.ERROR;
    operator = '$'; 
    val = -999;
  }
  
  // Initialize to a specific TokenType
  public Token (TokenType t)
  {
    type = t;
    operator = '$'; 
    val = -999;
  }
  
  // Set to a specific TokenType
  public void setToType(TokenType t)
  {
    type = t;
    operator = '$'; 
    val = -999;
  }
  
  // Set to a OPERATOR TokenType with specific operator value
  public void setToOperator(char c)
  {
    type = TokenType.OPERATOR;
    operator = c; 
    val = -999;
  }
  
  // Set to a VALUE TokenType with a specific numeric value
  public void setToValue(int v)
  {
    type = TokenType.VALUE;
    operator = '$'; 
    val = v;
  }
  
  // return true if the Current Token is of the given TokenType
  public boolean equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }
  
  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  public boolean equalsOperator(char c)
  {
    if (type == TokenType.OPERATOR && operator == c)
      return true;
    else
      return false;
  }
  
  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  public char getOperator ()
  {
    if (type == TokenType.OPERATOR)
      return operator;
    else
      return '$';   // using $ to indicate an error value
  }
  
  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  public int getValue()
  {
    if (type == TokenType.VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
  }
}