/**
 *  @file
 *  @author     This file has been generated by generate-bindings.pl. DO NOT MODIFY!
 *  @copyright  Simplified BSD
 *
 *  @cond
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the FreeBSD license as published by the FreeBSD
 *  project.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 *  You should have received a copy of the FreeBSD license along with this
 *  program. If not, see <http://www.opensource.org/licenses/bsd-license>.
 *  @endcond
 */

#ifndef JSCUint8ClampedArray_h
#define JSCUint8ClampedArray_h

#include <string>
#include "../../TypedArray.h"
#include "DOM/Node.hpp"
#include "JSCArrayBufferView.h"
#include <JavaScriptCore/JavaScriptCore.h>
#include "uscxml/plugins/datamodel/ecmascript/JavaScriptCore/JSCDOM.h"

namespace Arabica {
namespace DOM {

class JSCUint8ClampedArray {
public:
	struct JSCUint8ClampedArrayPrivate {
		JSCDOM* dom;
		uscxml::Uint8ClampedArray* nativeObj;
	};

	JSC_DESTRUCTOR(JSCUint8ClampedArrayPrivate);

	static JSValueRef getCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObj, size_t argumentCount, const JSValueRef* arguments, JSValueRef* exception);
	static JSValueRef setCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObj, size_t argumentCount, const JSValueRef* arguments, JSValueRef* exception);
	static JSValueRef subarrayCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObj, size_t argumentCount, const JSValueRef* arguments, JSValueRef* exception);

	static JSObjectRef jsConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
	static JSValueRef lengthAttrGetter(JSContextRef ctx, JSObjectRef thisObj, JSStringRef propertyName, JSValueRef* exception);
	static JSValueRef BYTES_PER_ELEMENTConstGetter(JSContextRef ctx, JSObjectRef thisObj, JSStringRef propertyName, JSValueRef* exception);
	static bool hasPropertyCustomCallback(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName);
	static JSValueRef getPropertyCustomCallback(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef* exception);
	static bool setPropertyCustomCallback(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);


	static JSStaticValue staticValues[];
	static JSStaticFunction staticFunctions[];

	static JSClassRef Tmpl;
	static JSClassRef getTmpl() {
		if (Tmpl == NULL) {
			JSClassDefinition classDef = kJSClassDefinitionEmpty;
			classDef.staticValues = staticValues;
			classDef.staticFunctions = staticFunctions;
			classDef.finalize = jsDestructor;
			classDef.hasProperty = hasPropertyCustomCallback;
			classDef.getProperty = getPropertyCustomCallback;
			classDef.setProperty = setPropertyCustomCallback;
			classDef.callAsConstructor = jsConstructor;
			classDef.parentClass = JSCArrayBufferView::getTmpl();

			Tmpl = JSClassCreate(&classDef);
			JSClassRetain(Tmpl);
		}
		return Tmpl;
	}


};

}
}

#endif // JSCUint8ClampedArray_h
