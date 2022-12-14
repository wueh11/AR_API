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

        for (size_t row = 0; row < _COLLIDER_LAYER; row++)
        {
            for (size_t col = 0; col < _COLLIDER_LAYER; col++)
            {
                if (mMatrix[row] & (1 << col)) {
                    //中宜昔走 焼観走 伊紫
                    LayerCollision(playScene, (eColliderLayer)row, (eColliderLayer)col);
                }
            }
        }
    }

    void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
    {
        /*
            けけけけ
            x けけけ
            x x けけ
            x x x け
            -> 企唖識奄層 神献楕幻 紫遂
        */
        //希 拙精 収切研 楳, 希 笛 収切研 伸稽
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
        // 乞窮 left 神崎詮闘級引 right 級聖 亜閃人辞 搾嘘背操醤 廃陥.
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
        ColliderID id; /// left, right税 id亜 杯団遭 葵昔 colliderid亜 持失吉陥.
        id.left = left->GetID();
        id.right = right->GetID();

        std::map<UINT64, bool>::iterator iter = mCollisionInformation.find(id.ID);

        if (iter == mCollisionInformation.end())
        {
            mCollisionInformation.insert(std::make_pair(id.ID, false));
            iter = mCollisionInformation.find(id.ID);
        }

        if (Intersect(left, right)) ///中宜端滴
        {
            // 中宜
            if (iter->second == false)
            {
                //置段 廃腰 中宜
                left->OnCollisionEnter(right);
                right->OnCollisionEnter(left);

                iter->second = true; /// 中宜掻
            }
            else
            {
                //中宜掻析凶
                left->OnCollisionStay(right);
                right->OnCollisionStay(left);
            }
        }
        else
        {
            // 中宜X
            if (iter->second == true)
            {
                // 中宜拭辞 匙閃蟹尽聖凶
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
    {   /// static昔 collider 舛左 clear(scene戚 痕井吃 凶 旋遂)
        memset(mMatrix, 0, sizeof(WORD) * _COLLIDER_LAYER);
    }
}