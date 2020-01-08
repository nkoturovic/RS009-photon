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
    PhotonUndo(rs::Image &&img, LabelImage* labelPtr, UndoPreview *undoPrevPtr);

    PhotonUndo();

    const rs::Image& origin() const;
    const rs::Image& current() const;

    template <class T>
    void action(T &&tform) {
        if (!m_imageLoaded)
            return;

        m_undo.action(std::forward<T>(tform));
        this->updateFriendComponents();
    }

    std::pair<bool, bool> undo();
    std::pair<bool, bool> redo();

    std::vector<std::shared_ptr<const rs::Transform>> previousActions() const;

    std::vector<std::shared_ptr<const rs::Transform>> nextActions() const;

    unsigned numOfPreviousActions() const;
    unsigned numOfNextActions() const;

private:
    ImageUndoType m_undo;
    bool m_imageLoaded = false;
    LabelImage *m_labelPtr = nullptr;
    UndoPreview *m_undoPreviewPtr = nullptr;

    void updateFriendComponents();


    void updateLabel();

    void updateUndoPreview();
};

#endif
