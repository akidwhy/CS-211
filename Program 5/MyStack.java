/*Abdullah Kidwai
  akidwa2
*/
public class MyStack {
  private StkNd head = null;
  
  public MyStack(){
    head = null;
  }
  
  public int isEmpty(){
    if(head == null){
      return 1;
    }
    else{
      return 0;
    }
  }

  public void push(Token t){
    StkNd tmp = new StkNd(t);
    tmp.next = head;
    head = tmp;
  }
  
  public Token top(){
    if(head != null){
      return head.piece;
    }
    else{
      return null;
    }
  }
  
  public void pop(){
    if(head != null){
      head = head.next;
    }
  }
  
  public class StkNd{
  Token piece;
  StkNd next;
  
  public StkNd(Token t){
    piece = t;
    next = null;
  }
}
}