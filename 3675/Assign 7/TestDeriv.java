// Name: Josh Weeks
// Date: 12/5/16
// Tabs: no tabs



public class TestDeriv
{
    public static void main(String args[])
    {
	Expression a, b, c, x, s, t, u, v, w, y, d1, d2, d3, d4, d5, d6;
        
        //sum testing
        System.out.println("SUM TESTING");
        a = new ConstantExpression(4.0);
	x = new VarExpression();
	s = new SumExpression(x, x);
        t = new SumExpression(x, a);
        d1 = s.deriv();
        d2 = t.deriv();
	System.out.println("deriv(" + s + ") = " + d1);
        System.out.println("deriv(" + t + ") = " + d2);
        
        //diff testing
        System.out.println("DIFFERENCE TESTING");
        a = new ConstantExpression(4.0);
        b = new ConstantExpression(2.0);
        c = new ConstantExpression(0.0);
	x = new VarExpression();
	s = new DiffExpression(a, b);
        t = new DiffExpression(x, a);
        u = new DiffExpression(x, c); // x - 0 = deriv x
        d1 = s.deriv();
        d2 = t.deriv();
        d3 = u.deriv();
	System.out.println("deriv(" + s + ") = " + d1);
        System.out.println("deriv(" + t + ") = " + d2);
        System.out.println("deriv(" + u + ") = " + d3);


        //multiplication testing
        System.out.println("MULTIPLICATION TESTING");
        a = new ConstantExpression(4.0);
        b = new ConstantExpression(1.0);
        c = new ConstantExpression(0.0);
	x = new VarExpression();
	s = new ProductExpression(a, b);
        t = new ProductExpression(x, c);
        u = new ProductExpression(c, x);
        v = new ProductExpression(b, x); 
        w = new ProductExpression(x, b); 
        y = new ProductExpression(x, a); 
        d1 = s.deriv();
        d2 = t.deriv();
        d3 = u.deriv();
        d4 = v.deriv();
        d5 = w.deriv();
        d6 = y.deriv();
	System.out.println("deriv(" + s + ") = " + d1);
        System.out.println("deriv(" + t + ") = " + d2);
        System.out.println("deriv(" + u + ") = " + d3);
        System.out.println("deriv(" + v + ") = " + d4);
        System.out.println("deriv(" + w + ") = " + d5);
        System.out.println("deriv(" + y + ") = " + d6);

        //constant power testing
        System.out.println("CONSTANT POWER TESTING");
        a = new ConstantExpression(4.0);
        b = new ConstantExpression(1.0);
        c = new ConstantExpression(0.0);
	x = new VarExpression();
	s = new ExpoExpression(a, b);
        t = new ExpoExpression(x, c);
        u = new ExpoExpression(x, a);
        w = new ExpoExpression(x, b);
        d1 = s.deriv();
        d2 = t.deriv();
        d3 = u.deriv();
        d5 = w.deriv();
	System.out.println("deriv(" + s + ") = " + d1);
        System.out.println("deriv(" + t + ") = " + d2);
        System.out.println("deriv(" + u + ") = " + d3);
        System.out.println("deriv(" + w + ") = " + d5);

    }
}

