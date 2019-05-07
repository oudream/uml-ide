package org.eclipse.uml2.diagram.activity.edit.policies;

import org.eclipse.gef.commands.Command;
import org.eclipse.gmf.runtime.emf.type.core.commands.DestroyReferenceCommand;
import org.eclipse.gmf.runtime.emf.type.core.requests.DestroyReferenceRequest;
import org.eclipse.uml2.diagram.activity.providers.UMLElementTypes;

/**
 * @generated
 */

public class ObjectNodeSelectionItemSemanticEditPolicy extends UMLBaseItemSemanticEditPolicy {

	/**
	 * @generated
	 */
	public ObjectNodeSelectionItemSemanticEditPolicy() {
		super(UMLElementTypes.ObjectNodeSelection_4004);
	}

	/**
	 * @generated
	 */
	protected Command getDestroyReferenceCommand(DestroyReferenceRequest req) {
		return getGEFWrapper(new DestroyReferenceCommand(req));
	}

}
