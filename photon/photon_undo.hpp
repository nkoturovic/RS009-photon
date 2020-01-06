#include <undo.hpp>
#include <rsimg/image.hpp>
#include <rsimg/transform.hpp>
#include <QImage>
#include "label_image.h"

using ImageUndoType = rs::Undo<rs::Image, rs::Transform>;
class PhotonUndo {
public:
    PhotonUndo(rs::Image &&img, LabelImage* labelPtr) : m_undo(std::move(img)), m_labelPtr(labelPtr) {
        this->updateLabel();
    }

    PhotonUndo() : PhotonUndo(rs::Image(), nullptr) {}

    const rs::Image& origin() const { return m_undo.origin(); }
    const rs::Image& current() const { return m_undo.current(); }

    template <class T>
    void action(T &&tform) {
        m_undo.action(std::forward<T>(tform));
        this->updateLabel();
    }

    std::pair<bool, bool> undo() { 
        auto retval = m_undo.undo(); 
        this->updateLabel();
        return retval;
    }
    std::pair<bool, bool> redo() {
        auto retval = m_undo.redo();
        this->updateLabel();
        return retval;
    }

    std::vector<std::shared_ptr<const rs::Transform>> previousActions() {
        return m_undo.previousActions();
    }

    std::vector<std::shared_ptr<const rs::Transform>> nextActions() {
        return m_undo.nextActions();
    }

    unsigned numOfPreviousActions() const { return m_undo.numOfPreviousActions(); }
    unsigned numOfNextActions() const { return m_undo.numOfNextActions(); }

private:
    ImageUndoType m_undo;
    LabelImage *m_labelPtr;

    void updateLabel() {
        if (m_labelPtr == nullptr)
            return;

        const rs::Image &imgRef = this->current();
        QImage qimg = QImage(imgRef.data(), imgRef.width(), imgRef.height(), imgRef.step(), QImage::Format_BGR888);
        m_labelPtr->setPixmap(QPixmap::fromImage(std::move(qimg)));
    }
};
