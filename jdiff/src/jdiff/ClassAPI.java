package jdiff;

import java.io.*;
import java.util.*;

/** 
 * Class to represent a class, analogous to ClassDoc in the 
 * Javadoc doclet API. 
 * 
 * The method used for Collection comparison (compareTo) must make its
 * comparison based upon everything that is known about this class.
 *
 * See the file LICENSE.txt for copyright details.
 * @author Matthew Doar, mdoar@pobox.com
 */
class ClassAPI implements Comparable<ClassAPI> {

    /** Name of the class, not fully qualified. */
    public String name_;

    /** Set if this class is an interface. */
    public boolean isInterface_;

    /** Set if this class is abstract. */
    boolean isAbstract_ = false;

    /** Modifiers for this class. */
    public Modifiers modifiers_;

    /** Name of the parent class, or null if there is no parent. */
    public String extends_; // Can only extend zero or one class or interface

    /** Interfaces implemented by this class. */
    public final List<String> implements_ = new ArrayList<>();

    /** Constructors in this class. */
    public final List<ConstructorAPI> ctors_ = new ArrayList<>();

    /** Methods in this class. */
    public final List<MethodAPI> methods_ = new ArrayList<>();

    /** Fields in this class. */
    public final List<FieldAPI> fields_ = new ArrayList<>();

    /** The doc block, default is null. */
    public String doc_ = null;

    /** Constructor. */
    public ClassAPI(String name, String parent, boolean isInterface, 
                    boolean isAbstract, Modifiers modifiers) {
        name_ = name;
        extends_ = parent;
        isInterface_ = isInterface;
        isAbstract_ = isAbstract;
        modifiers_ = modifiers;
    }

    /** Compare two ClassAPI objects by all the known information. */
    public int compareTo(ClassAPI o) {
        ClassAPI oClassAPI = (ClassAPI)o;
        int comp = name_.compareTo(oClassAPI.name_);
        if (comp != 0)
            return comp;
        if (isInterface_ != oClassAPI.isInterface_)
            return -1;
        if (isAbstract_ != oClassAPI.isAbstract_)
            return -1;
        comp = modifiers_.compareTo(oClassAPI.modifiers_);
        if (comp != 0)
            return comp;
        if (APIComparator.docChanged(doc_, oClassAPI.doc_))
            return -1;
        return 0;
    }  

    /** 
     * Tests two methods for equality using just the class name, 
     * used by indexOf(). 
     */
    public boolean equals(Object o) {
        if (name_.compareTo(((ClassAPI)o).name_) == 0)
            return true;
        return false;
    }
    
}
