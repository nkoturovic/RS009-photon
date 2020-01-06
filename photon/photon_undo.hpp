#include <undo.hpp>
#include <rsimg/image.hpp>
#include <rsimg/transform.hpp>
#include <QImage>

using ImageUndoType = rs::Undo<rs::Image, rs::Transform>;
class PhotonUndo {
public:
    PhotonUndo(rs::Image &&img) : m_undo(std::move(img)) {
        this->updateQimg();
    }

    PhotonUndo() : PhotonUndo(rs::Image()) {}

    const rs::Image& origin() const { return m_undo.origin(); }
    const rs::Image& current() const { return m_undo.current(); }
    QImage* qimagePtr() { return &m_qimage; }

    template <class T>
    void action(T &&tform) {
        m_undo.action(std::forward<T>(tform));
        this->updateQimg();
    }

    std::pair<bool, bool> undo() { 
        auto retval = m_undo.undo(); 
        this->updateQimg();
        return retval;
    }
    std::pair<bool, bool> redo() {
        auto retval = m_undo.redo();
        this->updateQimg();
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
    QImage m_qimage;

    void updateQimg() {
        const rs::Image &imgRef = this->current();
        m_qimage = QImage(imgRef.data(), imgRef.width(), imgRef.height(), imgRef.step(), QImage::Format_BGR888);
    }
};
