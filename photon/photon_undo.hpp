#ifndef PHOTON_UNDO_H
#define PHOTON_UNDO_H

#include <undo.hpp>
#include <rsimg/image.hpp>
#include <rsimg/transform.hpp>
#include <QImage>
#include "label_image.h"
#include "undopreview.h"

using ImageUndoType = rs::Undo<rs::Image, rs::Transform>;
class PhotonUndo {
public:
    PhotonUndo(rs::Image &&img, LabelImage* labelPtr, UndoPreview *undoPrevPtr)
        : m_undo(std::move(img)),
          m_labelPtr(labelPtr),
          m_undoPreviewPtr(undoPrevPtr)
    {
        this->updateLabel();
    }

    PhotonUndo() : PhotonUndo(rs::Image(), nullptr, nullptr) {}

    const rs::Image& origin() const { return m_undo.origin(); }
    const rs::Image& current() const { return m_undo.current(); }

    template <class T>
    void action(T &&tform) {
        m_undo.action(std::forward<T>(tform));
        this->updateFriendComponents();
    }

    std::pair<bool, bool> undo() { 
        auto retval = m_undo.undo();
        this->updateFriendComponents();
        return retval;
    }
    std::pair<bool, bool> redo() {
        auto retval = m_undo.redo();
        this->updateFriendComponents();
        return retval;
    }

    std::vector<std::shared_ptr<const rs::Transform>> previousActions() const {
        return m_undo.previousActions();
    }

    std::vector<std::shared_ptr<const rs::Transform>> nextActions() const {
        return m_undo.nextActions();
    }

    unsigned numOfPreviousActions() const { return m_undo.numOfPreviousActions(); }
    unsigned numOfNextActions() const { return m_undo.numOfNextActions(); }

private:
    ImageUndoType m_undo;
    LabelImage *m_labelPtr = nullptr;
    UndoPreview *m_undoPreviewPtr = nullptr;

    void updateFriendComponents() {
        this->updateLabel();
        this->updateUndoPreview();
    }


    void updateLabel() {
        if (m_labelPtr == nullptr)
            return;

        const rs::Image &imgRef = this->current();
        QImage qimg = QImage(imgRef.data(), imgRef.width(), imgRef.height(), imgRef.step(), QImage::Format_BGR888);
        m_labelPtr->setPixmap(QPixmap::fromImage(std::move(qimg)));
    }

    void updateUndoPreview() {

        if (m_undoPreviewPtr == nullptr)
            return;

        this->m_undoPreviewPtr->updatePreview(
            m_undo.previousActions(),
            m_undo.nextActions()
        );
    }
};

#endif
