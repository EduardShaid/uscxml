package org.uscxml.apache.commons.scxml2;

import org.uscxml.Factory;
import org.uscxml.dm.jexl.JEXLDataModel;

public class JexlEvaluator extends Evaluator {

	public JexlEvaluator() {

	}
	
	@Override
	public Context newContext(Object object) {
		// TODO Auto-generated method stub
		Context ctx = new Context();
		ctx.dm = new JEXLDataModel(); 
		return ctx;
	}
}
