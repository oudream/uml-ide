package org.eclipse.uml2.diagram.csd.action;

import org.eclipse.uml2.diagram.common.actions.ConvertCommentCommandBase;
import org.eclipse.uml2.diagram.common.actions.ConvertNoteToCommentAction;
import org.eclipse.uml2.diagram.csd.edit.parts.CommentAnnotatedElementEditPart;
import org.eclipse.uml2.diagram.csd.edit.parts.CommentEditPart;
import org.eclipse.uml2.diagram.csd.providers.UMLElementTypes;

/**
 * @generated
 */

public class TurnNoteIntoCommentAction extends ConvertNoteToCommentAction {

	/**
	 * @generated
	 */
	public TurnNoteIntoCommentAction() {
		super(new ConvertCommentCommandBase.ConfigImpl(CommentEditPart.VISUAL_ID, CommentAnnotatedElementEditPart.VISUAL_ID, UMLElementTypes.CommentAnnotatedElement_4016));
	}
}
