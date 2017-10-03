// Name: Josh Weeks
// Date: 12/5/16
// Tabs: no tabs

import java.io.*;

//==========================================================
//                     Class Expression
//==========================================================


abstract class Expression
{
  //-----------------------------------------------------
  // simplify() returns a possibly simplified version of
  // this expression.
  //-----------------------------------------------------

  public abstract Expression simplify();

  //-----------------------------------------------------
  // toString() returns a string that described this
  // expression.  It can be used for printing this
  // expression.
  //-----------------------------------------------------

  public abstract String toString();

  //-----------------------------------------------------
  // rawderiv() returns the derivative of this expression,
  // without simplification.
  //-----------------------------------------------------

  public abstract Expression rawderiv();

  //-----------------------------------------------------
  // deriv() returns the derivative of this expression,
  // with simplification.
  //-----------------------------------------------------

  public Expression deriv()
  {
      return rawderiv().simplify();
  }
}

//==========================================================
//                     Class ConstantExpression
//==========================================================
// A constant expression is the expression equivalent of a
// real number.
//==========================================================

class ConstantExpression extends Expression
{
  private double value;

  public ConstantExpression(double v)
  {
    value = v;
  }

  public Expression rawderiv()
  {
    return new ConstantExpression(0.0);
  }

  public Expression simplify()
  {
    return this;
  }

  public String toString()
  {
    return "" + value;
  }

  public double getvalue()
  {
    return value;
  }
}

//==========================================================
//                     Class VarExpression
//==========================================================
// A VarExpression is the independent variable x.
//==========================================================

class VarExpression extends Expression
{
  public VarExpression()
  {
  }

  public Expression rawderiv()
  {
    return new ConstantExpression(1.0);
  }

  public Expression simplify()
  {
    return this;
  }

  public String toString()
  {
    return "x";
  }

}



//==========================================================
//                    Class SumExpression
//==========================================================
// A SumExpression is an expression that is the sum of two
// other expressions.
//==========================================================

class SumExpression extends Expression
{
  private Expression addend1, addend2;

  public SumExpression(Expression e1, Expression e2)
  {
    addend1 = e1;
    addend2 = e2;
  }

  public Expression rawderiv()
  {
    return new SumExpression(addend1.rawderiv(), addend2.rawderiv());
  }

  public Expression simplify()
  {
    return simplifySum(addend1.simplify(), addend2.simplify());
  }

  public String toString()
  {
    return "(" + addend1.toString() + "+" + addend2.toString() + ")";
  }

  private static Expression simplifySum(Expression e1, Expression e2)
  {
    // 0 + x = x and constant arithmetic

    if(e1 instanceof ConstantExpression) {
      ConstantExpression ce = (ConstantExpression) e1;

      // 0 + x = x

      if(ce.getvalue() == 0.0) {
        return e2;
      }

      // Constant arithmetic 

     if(e2 instanceof ConstantExpression) {
      ConstantExpression ce2 = (ConstantExpression) e2;
      return new ConstantExpression(ce.getvalue() + ce2.getvalue());
     }

    }

    // x + 0 = x

    if(e2 instanceof ConstantExpression) {
      ConstantExpression ce = (ConstantExpression) e2;
      if(ce.getvalue() == 0.0) {
          return e1;
      }
    }

    // Default: do not simplify.

    return new SumExpression(e1, e2);

  }
}



//==========================================================
//                    Class DiffExpression
//==========================================================
// A DiffExpression is an expression that is the difference
// of two other expressions.
//==========================================================

class DiffExpression extends Expression
{
  private Expression sub1, sub2;

  public DiffExpression(Expression e1, Expression e2)
  {
    sub1 = e1;
    sub2 = e2;
  }

  public Expression rawderiv()
  {
    return new DiffExpression(sub1.rawderiv(), sub2.rawderiv());
  }

  public Expression simplify()
  {
    return simplifyDiff(sub1.simplify(), sub2.simplify());
  }

  public String toString()
  {
    return "(" + sub1.toString() + "-" + sub2.toString() + ")";
  }

  private static Expression simplifyDiff(Expression e1, Expression e2)
  {

    if(e2 instanceof ConstantExpression) {
      ConstantExpression ce2 = (ConstantExpression) e2;

      // a - 0 = a

      if(ce2.getvalue() == 0.0) {
        return e1;
      }

      // Constant arithmetic 

     if(e1 instanceof ConstantExpression) {
      ConstantExpression ce = (ConstantExpression) e1;
      return new ConstantExpression(ce.getvalue() - ce2.getvalue());
      }
    }

    // Default: do not simplify.

    return new DiffExpression(e1, e2);

  }
}



//==========================================================
//                    Class ProductExpression
//==========================================================
// A ProductExpression is an expression that is the product
// of two other expressions.
//==========================================================

class ProductExpression extends Expression
{
  private Expression mult1, mult2;

  public ProductExpression(Expression e1, Expression e2)
  {
    mult1 = e1;
    mult2 = e2;
  }

  public Expression rawderiv()
  {
    return new SumExpression(new ProductExpression(mult1, mult2.rawderiv()), new ProductExpression(mult1.rawderiv(), mult2));
  }

  public Expression simplify()
  {
    return simplifyProduct(mult1.simplify(), mult2.simplify());
  }

  public String toString()
  {
    return "(" + mult1.toString() + "*" + mult2.toString() + ")";
  }

  private static Expression simplifyProduct(Expression e1, Expression e2)
  {
    if(e1 instanceof ConstantExpression) {
      ConstantExpression ce = (ConstantExpression) e1;

      // 0 * x = 0

      if(ce.getvalue() == 0.0) {
        return e1;
      }
      
      // 1 * x = x
      
      if(ce.getvalue() == 1.0) {
        return e2;
      }

      if(e2 instanceof ConstantExpression) {
       ConstantExpression ce2 = (ConstantExpression) e2; 

       // Constant arithmetic

       return new ConstantExpression(ce.getvalue() * ce2.getvalue());
      }

    }

    if(e2 instanceof ConstantExpression) {
      ConstantExpression ce2 = (ConstantExpression) e2;
      
      // x * 0 = 0
      
      if(ce2.getvalue() == 0.0) {
        return e2;
      }

      // x * 1 = x

      if(ce2.getvalue() == 1.0) {
        return e1;
      }  
    }

    // Default: do not simplify.

    return new ProductExpression(e1, e2);

  }
}
  
  
  
//==========================================================
//                    Class ExpoExpression
//==========================================================
// A ExpoExpression is an expression that is the exponentiation
// of two other expressions.
//==========================================================

class ExpoExpression extends Expression
{
  private Expression expo1, expo2;

  public ExpoExpression(Expression e1, Expression e2)
  {
    expo1 = e1;
    expo2 = e2;
  }

  public Expression rawderiv()
  {
    if(expo2 instanceof ConstantExpression){
      ConstantExpression ce = new ConstantExpression(1);
      DiffExpression diffe = new DiffExpression(expo2, ce);
      ExpoExpression expoe = new ExpoExpression(expo1, diffe);
      ProductExpression ine = new ProductExpression(expo2, expoe);
      return new ProductExpression(ine, expo1.deriv());
    }
    return null;
  }

  public Expression simplify()
  {
    return simplifyExpo(expo1.simplify(), expo2.simplify());
  }

  public String toString()
  {
    return "(" + expo1.toString() + "^" + expo2.toString() + ")";
  }

  private static Expression simplifyExpo(Expression e1, Expression e2)
  {
    if(e1 instanceof ConstantExpression) {
      ConstantExpression ce = (ConstantExpression) e1;

      if(e2 instanceof ConstantExpression) {
        ConstantExpression ce2 = (ConstantExpression) e2; 

        // Constant arithmetic

        return new ConstantExpression(Math.pow(ce.getvalue(), ce2.getvalue()));
     }

    }

    if(e2 instanceof ConstantExpression) {
      ConstantExpression ce2 = (ConstantExpression) e2;
      
      // x ^ 1 = x
      
      if(ce2.getvalue() == 1.0) {
        return e1;
      }

      // x ^ 0 = 0

      if(ce2.getvalue() == 0.0) {
        return e2;
      }  
    }

    // Default: do not simplify.

    return new ProductExpression(e1, e2);

  }
  
}
