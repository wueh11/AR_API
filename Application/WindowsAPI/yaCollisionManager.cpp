#include "yaCollisionManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaGameObject.h"
#include "yaCollider.h"
#include "yaInput.h"

namespace ya
{
    WORD CollisionManager::mMatrix[_COLLIDER_LAYER] = {};
    std::map<UINT64, bool> CollisionManager::mCollisionInformation;
    bool CollisionManager::mbShow = false;

    void CollisionManager::Tick()
    {
        if (KEY_DOWN(eKeyCode::C))
            mbShow = !mbShow;

        Scene* playScene = SceneManager::GetPlayScene();

        if (!playScene->IsActive())
            return;

        for (size_t row = 0; row < _COLLIDER_LAYER; row++)
        {
            for (size_t col = 0; col < _COLLIDER_LAYER; col++)
            {
                if (mMatrix[row] & (1 << col)) {
                    //�浹���� �ƴ��� �˻�
                    LayerCollision(playScene, (eColliderLayer)row, (eColliderLayer)col);
                }
            }
        }
    }

    void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
    {
        /*
            ��������
            x ������
            x x ����
            x x x ��
            -> �밢������ �����ʸ� ���
        */
        //�� ���� ���ڸ� ��, �� ū ���ڸ� ����
        UINT row = 0;
        UINT col = 0;

        UINT iLeft = (UINT)left;
        UINT iRight = (UINT)right;

        if (iLeft < iRight)
        {
            row = (UINT)left;
            col = (UINT)right;
        }
        else
        {
            row = (UINT)right;
            col = (UINT)left;
        }

        if (value == true)
            mMatrix[row] |= (1 << col);
        else
            mMatrix[row] &= ~(1 << col);

    }

    void CollisionManager::LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right)
    {
        // ��� left ������Ʈ��� right ���� �����ͼ� ������� �Ѵ�.
        std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
        std::vector<GameObject*>& rights = scene->GetGameObjects(right);

        for (auto leftObject : lefts)
        {
            Collider* leftCollider = leftObject->GetComponent<Collider>();
            if (leftCollider == nullptr)
                continue;

            for (auto rightObject : rights)
            {
                Collider* rightCollider = rightObject->GetComponent<Collider>();

                if (rightCollider == nullptr)
                    continue;

                if (leftObject == rightObject)
                    continue;

                ColliderCollision(leftCollider, rightCollider);
            }
        }
    }

    void CollisionManager::ColliderCollision(Collider* left, Collider* right)
    {
        ColliderID id; /// left, right�� id�� ������ ���� colliderid�� �����ȴ�.
        id.left = left->GetID();
        id.right = right->GetID();

        std::map<UINT64, bool>::iterator iter = mCollisionInformation.find(id.ID);

        if (iter == mCollisionInformation.end())
        {
            mCollisionInformation.insert(std::make_pair(id.ID, false));
            iter = mCollisionInformation.find(id.ID);
        }

        if (Intersect(left, right)) ///�浹üũ
        {
            // �浹
            if (iter->second == false)
            {
                //���� �ѹ� �浹
                left->OnCollisionEnter(right);
                right->OnCollisionEnter(left);

                iter->second = true; /// �浹��
            }
            else
            {
                //�浹���϶�
                left->OnCollisionStay(right);
                right->OnCollisionStay(left);
            }
        }
        else
        {
            // �浹X
            if (iter->second == true)
            {
                // �浹���� ������������
                left->OnCollisionExit(right);
                right->OnCollisionExit(left);

                iter->second = false;
            }
        }
    }

    bool CollisionManager::Intersect(Collider* left, Collider* right)
    {
        if (left->GetOwner()->IsDeath())
            return false;
        if (right->GetOwner()->IsDeath())
            return false;

        Vector2 leftPos = left->GetPos();
        Vector2 leftSize = left->GetSize();
        Vector2 leftScale = left->GetScale();

        Vector2 rightPos = right->GetPos();
        Vector2 rightSize = right->GetSize();
        Vector2 rightScale = right->GetScale();

        if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x * leftScale.x / 2.0f + rightSize.x * rightScale.x / 2.0f)
            && fabs(leftPos.y - rightPos.y) < fabs(leftSize.y * leftScale.y / 2.0f + rightSize.y * rightScale.y / 2.0f))
        {
            return true;
        }

        return false;
    }

    void CollisionManager::Clear()
    {   /// static�� collider ���� clear(scene�� ����� �� ����)
        memset(mMatrix, 0, sizeof(WORD) * _COLLIDER_LAYER);
    }
}